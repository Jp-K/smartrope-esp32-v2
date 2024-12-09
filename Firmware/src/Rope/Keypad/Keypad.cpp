#include "Rope/Keypad/Keypad.hpp"

#include <Arduino.h>

#include "Rope/IoT/Event.hpp"
#include "Rope/RopeToy.hpp"

namespace Rope
{
    Keypad::Keypad(RopeToy& rope, uint8_t pin) : NamedEntity("Keypad"),
        rope(rope),
        pin(pin),
        parameters(rope)
    {
        pinMode(pin, INPUT);
    }

    bool Keypad::isOn() const
    {
        return rope.config.keypadEnabled.get();
    }

    bool Keypad::isOff() const
    {
        return !isOn();
    }

    void Keypad::turnOn(const std::string& requester)
    {
        if (isOff())
        {
            startListening();
            rope.config.keypadEnabled.set(true);

            notifyKeypadTuned(requester);
        }
    }

    void Keypad::turnOff(const std::string& requester)
    {
        if (isOn())
        {
            stopListening();
            rope.config.keypadEnabled.set(false);

            notifyKeypadTuned(requester);
        }
    }

    //void Keypad::startListening()
    //{
    //    h4pUserEvent("Start listening keypad", NULL);
    //    uint32_t updateInterval = parameters.getUpdateInterval();

    //    debounceTimer.start();
    //    repeatTimer.start();
    //    canRepeat = false;
    //    listenTask = h4.every(updateInterval, [this] { listen(); });
    //}

    struct TaskParams {
        Keypad* keypadPtr;
    };

    void listenPeriodically(void *pvParameters)
    {
        TaskParams* params = static_cast<TaskParams*>(pvParameters);
        Keypad* keypadPtr = params->keypadPtr;

        uint32_t updateInterval = keypadPtr->parameters.getUpdateInterval();

        while (keypadPtr->activeListening)
        {
            keypadPtr->listen();
            vTaskDelay(updateInterval / portTICK_PERIOD_MS);
        }
        delete params;
        vTaskDelete(nullptr);
    }
    
    void Keypad::startListening()
    {
        uint32_t updateInterval = parameters.getUpdateInterval();
        TaskParams* param = new TaskParams{ this };

        //Serial.println("entrou listening");
        //Serial.println("entrou listening");
        //Serial.println("entrou listening");
        delay(500);

        debounceTimer.start();
        repeatTimer.start();
        canRepeat = false;
        activeListening = true;

        xTaskCreatePinnedToCore(
            listenPeriodically,      // Função que será executada na tarefa
            "ListenTask",            // Nome da tarefa
            8192,                    // Tamanho da pilha da tarefa
            param,                    // Parâmetro passado para a função
            1,                       // Prioridade da tarefa
            &listenTaskHandle,       // Handle da tarefa
            1                        // Core (CPU) onde a tarefa será executada
        );
    }

    
    void Keypad::stopListening()
    {
        if (activeListening)
        {
            activeListening = false;  // Para a execução da tarefa

            if (listenTaskHandle != nullptr)
            {
                vTaskDelete(listenTaskHandle);  // Deleta a tarefa
                listenTaskHandle = nullptr;
            }
        }
    }

    void Keypad::restart()
    {
        if (isOn())
        {
            stopListening();
            startListening();
        }
    }

    void Keypad::initialize()
    {
        parameters.setDebounceInterval(rope.config.keypadDebounceInterval.get());
        parameters.setUpdateInterval(rope.config.keypadUpdateInterval.get());
        //rope.sound.play("", Note::E, 7, 0.045f, 0.075f, nullptr, nullptr);
        //rope.sound.play("", Note::D, 7, 0.045f, 0.075f, nullptr, nullptr);
        //rope.sound.play("", Note::Cs, 7, 0.135f, 0.0f, nullptr, nullptr);

        // buttons.front.press(Event::Origin::User, rope);
        // delay(500);
        // buttons.center.press(Event::Origin::User, rope);

        if (isOn())
        {
            startListening();
        }
    }

    void Keypad::listen()
    {
        uint16_t value = analogRead(pin);
        uint32_t debounceInterval = parameters.getDebounceInterval();

        unsigned long timeElapsed = debounceTimer.timeElapsed(Timer::UnitOfTime::Milliseconds);

        if (timeElapsed < debounceInterval)
        {
            return;
        }

        for (auto button : buttons.all())
        {
            if (button->getRange().contains(value))
            {
                button->setCurrentState(ButtonState::DOWN);
                processClick(button);
            }
            else
            {
                button->setCurrentState(ButtonState::UP);
            }
        }

        debounceTimer.start();
    }

    void Keypad::processClick(Button* button)
    {
        ButtonState before = button->getPreviousState();
        ButtonState now = button->getCurrentState();

        if (before == ButtonState::UP && now == ButtonState::DOWN)
        {
            button->press(Event::Origin::User, rope);
            keypadRepeatDelayTimer.start();
            canRepeat = true;
        }
        // else if (before == ButtonState::DOWN && now == ButtonState::DOWN)
        // {
        //     uint32_t repeatInterval = rope.config.keypadRepeatInterval.get();
        //     uint32_t lastRepeat = repeatTimer.timeElapsed(Timer::UnitOfTime::Milliseconds);

        //     if (canRepeat && lastRepeat >= repeatInterval)
        //     {
        //         button->press(Event::Origin::User, rope);
        //         repeatTimer.start();
        //     }
        // }
        // else
        // {
        //     canRepeat = false;
        // }
    }

    KeypadParameters Keypad::getKeypadParameters() const
    {
        return parameters;
    }

    void Keypad::setKeypadParameters(const std::string& requester, const KeypadParameters& parameters)
    {
        rope.config.keypadDebounceInterval.set(parameters.getDebounceInterval());
        rope.config.keypadUpdateInterval.set(parameters.getUpdateInterval());

        this->parameters.setUpdateInterval(parameters.getUpdateInterval());
        this->parameters.setDebounceInterval(parameters.getDebounceInterval());

        restart();
        notifyKeypadTuned(requester);
    }

    void Keypad::notifyKeypadTuned(const std::string& requester)
    {
        KeypadTunedEvent event(requester, parameters, isOn());
        rope.IoT.notifyEvent(&event);
    }

} // namespace Rope