#include "RopeToy.hpp"

#include <cmath>

#include "Rope/IoT/Commands/MoveCommand.hpp"
#include "Rope/IoT/Commands/RotateCommand.hpp"
#include "Rope/IoT/Commands/ToggleLedCommand.hpp"
#include "Rope/IoT/Events/MoveStartedEvent.hpp"
#include "Rope/IoT/Events/MoveFinishedEvent.hpp"
#include "Rope/IoT/Events/RotationStartedEvent.hpp"
#include "Rope/IoT/Events/RotationFinishedEvent.hpp"
#include <Arduino.h>

#define INFO_PREFIX "Rope"
#define ERROR_PREFIX INFO_PREFIX " error:"

namespace Rope
{
    RopeToy::RopeToy() :
        config(),
        IoT(*this),
        leds(*this),
        sound(*this, pins.buzzer, 0),
        battery(*this, pins.battery, pins.charger, config.batterySamples.get(), config.batteryCriticalLevel.get()),
        keypad(*this, pins.keypad),
        motors(*this),
        cinematics(*this),
        program(*this)
    {
        Serial.println("entrou construtor ropetoy");
    }

    void RopeToy::initialize()
    {
        // config.initialize();
        battery.initialize();
        keypad.initialize();
        

        // h4pUserEvent("Rope initialized", NULL);
    }

    void RopeToy::moveForward(const std::string& requester, AsyncStartCallback startCallback, AsyncFinishCallback finishCallback)
    {
        MoveParameters parameters = getDefaultMoveParameters();
        moveForward(requester, parameters, startCallback, finishCallback);
    }

    void RopeToy::moveForward(const std::string& requester, MoveParameters parameters, AsyncStartCallback startCallback, AsyncFinishCallback finishCallback)
    {
        parameters.setDirection(MoveParameters::Direction::Forward);
        move(requester, parameters, startCallback, finishCallback);
    }

    void RopeToy::moveBackward(const std::string& requester, AsyncStartCallback startCallback, AsyncFinishCallback finishCallback)
    {
        MoveParameters parameters = getDefaultMoveParameters();
        moveBackward(requester, parameters, startCallback, finishCallback);
    }

    void RopeToy::moveBackward(const std::string& requester, MoveParameters parameters, AsyncStartCallback startCallback, AsyncFinishCallback finishCallback)
    {
        parameters.setDirection(MoveParameters::Direction::Backward);
        move(requester, parameters, startCallback, finishCallback);
    }

    void RopeToy::rotateClockwise(const std::string& requester, AsyncStartCallback startCallback, AsyncFinishCallback finishCallback)
    {
        RotationParameters parameters = getDefaultRotationParameters();
        rotateClockwise(requester, parameters, startCallback, finishCallback);
    }

    void RopeToy::rotateClockwise(const std::string& requester, RotationParameters parameters, AsyncStartCallback startCallback, AsyncFinishCallback finishCallback)
    {
        parameters.setDirection(RotationParameters::Direction::Clockwise);
        rotate(requester, parameters, startCallback, finishCallback);
    }

    void RopeToy::rotateCounterClockwise(const std::string& requester, AsyncStartCallback startCallback, AsyncFinishCallback finishCallback)
    {
        RotationParameters parameters = getDefaultRotationParameters();
        rotateCounterClockwise(requester, parameters, startCallback, finishCallback);
    }

    void RopeToy::rotateCounterClockwise(const std::string& requester, RotationParameters parameters, AsyncStartCallback startCallback, AsyncFinishCallback finishCallback)
    {
        parameters.setDirection(RotationParameters::Direction::CounterClockwise);
        rotate(requester, parameters, startCallback, finishCallback);
    }

    void RopeToy::move(const std::string& requester, MoveParameters parameters, AsyncStartCallback startCallback, AsyncFinishCallback finishCallback)
    {
        if (cantMoveOrRotate())
        {
            return;
        }

        StepperMotor::Direction leftMotorDirection;
        StepperMotor::Direction rightMotorDirection;
        Serial.println("entrou move");

        switch (parameters.getDirection())
        {
        case MoveParameters::Direction::Forward:
            leftMotorDirection = StepperMotor::Direction::CounterClockwise;
            rightMotorDirection = StepperMotor::Direction::Clockwise;
            break;
        case MoveParameters::Direction::Backward:
            leftMotorDirection = StepperMotor::Direction::Clockwise;
            rightMotorDirection = StepperMotor::Direction::CounterClockwise;
            break;
        }
        Serial.println("entrou move1");

        auto finished = [this, requester, parameters, finishCallback](float timeElapsed, uint32_t stepsPerformed)
        {
            float distanceTraveled = cinematics.motorStepsToBodyDisplacement(stepsPerformed);

            // Copy the object, so we can change some values
            MoveParameters params = parameters;

            params.setDistance(distanceTraveled);
            params.setDuration(timeElapsed);

            moveFinished(requester, params, finishCallback);
        };
        Serial.println("entrou move2");

        float stepsPerSecond = cinematics.bodyDisplacementToMotorSteps(parameters.getSpeed());

        if (parameters.mustMoveForever())
        {
            moveStarted(requester, parameters, startCallback);
            motors.synchronizedMoveForever(stepsPerSecond, leftMotorDirection, rightMotorDirection, finished);

            return;
        }
        Serial.println("entrou move3");

        if (parameters.getDuration() > 0.0f)
        {
            moveStarted(requester, parameters, startCallback);
            motors.synchronizedMoveInterval(parameters.getDuration(), stepsPerSecond, leftMotorDirection, rightMotorDirection, finished);

            return;
        }
        Serial.println("entrou move4");

        uint32_t stepsRequired = std::round(cinematics.bodyDisplacementToMotorSteps(parameters.getDistance()));
        float timeRequired = motors.stepsToSeconds(stepsRequired, stepsPerSecond);

        //h4pUserEvent(INFO_PREFIX " steps required to move: %d", stepsRequired);
        //h4pUserEvent(INFO_PREFIX " steps per second: %.2f", stepsPerSecond);

        parameters.setDuration(timeRequired);
        moveStarted(requester, parameters, startCallback);
        Serial.println("entrou move5");

        motors.synchronizedMoveSteps(stepsRequired, stepsPerSecond, leftMotorDirection, rightMotorDirection, finished);
        Serial.println("entrou move6");
    }

    void RopeToy::rotate(const std::string& requester, RotationParameters parameters, AsyncStartCallback startCallback, AsyncFinishCallback finishCallback)
    {
        if (cantMoveOrRotate())
        {
            return;
        }

        StepperMotor::Direction leftMotorDirection;
        StepperMotor::Direction rightMotorDirection;

        switch (parameters.getDirection())
        {
        case RotationParameters::Direction::Clockwise:
            leftMotorDirection = StepperMotor::Direction::CounterClockwise;
            rightMotorDirection = StepperMotor::Direction::CounterClockwise;
            break;
        case RotationParameters::Direction::CounterClockwise:
            leftMotorDirection = StepperMotor::Direction::Clockwise;
            rightMotorDirection = StepperMotor::Direction::Clockwise;
            break;
        }

        auto finished = [this, requester, parameters, finishCallback](float timeElapsed, uint32_t stepsPerformed)
        {
            float degreesRotated = cinematics.motorStepsToBodyRotation(stepsPerformed);

            // Copy the object, so we can change some values
            RotationParameters params = parameters;

            params.setDegrees(degreesRotated);
            params.setDuration(timeElapsed);

            rotationFinished(requester, params, finishCallback);
        };

        float stepsPerSecond = cinematics.bodyRotationToMotorSteps(parameters.getSpeed());

        if (parameters.mustRotateForever())
        {
            rotationStarted(requester, parameters, startCallback);
            motors.synchronizedMoveForever(stepsPerSecond, leftMotorDirection, rightMotorDirection, finished);

            return;
        }

        if (parameters.getDuration() > 0.0f)
        {
            rotationStarted(requester, parameters, startCallback);
            motors.synchronizedMoveInterval(parameters.getDuration(), stepsPerSecond, leftMotorDirection, rightMotorDirection, finished);

            return;
        }

        uint32_t stepsRequired = std::round(cinematics.bodyRotationToMotorSteps(parameters.getDegrees()));
        float timeRequired = motors.stepsToSeconds(stepsRequired, stepsPerSecond);

        //h4pUserEvent(INFO_PREFIX " steps required to rotate: %d", stepsRequired);
        //h4pUserEvent(INFO_PREFIX " steps per second: %.2f", stepsPerSecond);

        parameters.setDuration(timeRequired);
        rotationStarted(requester, parameters, startCallback);

        motors.synchronizedMoveSteps(stepsRequired, stepsPerSecond, leftMotorDirection, rightMotorDirection, finished);
    }

    void RopeToy::moveStarted(const std::string& requester, MoveParameters parameters, AsyncStartCallback startCallback)
    {
        moving = true;
        stopRequester.clear();

        if (startCallback)
        {
            AsyncActionStart result;
            result.setExecutionRequester(requester);
            startCallback(result);
        }

        MoveStartedEvent event(requester, parameters);
        IoT.notifyEvent(&event);

        toggleMoveLed(requester, parameters, HIGH);
        Serial.println("antes do play melody");
        playMoveMelody(requester, parameters);
    }

    void RopeToy::moveFinished(const std::string& requester, MoveParameters parameters, AsyncFinishCallback finishCallback)
    {
        Serial.println("entrou toggle led");
        toggleMoveLed(requester, parameters, LOW);
        Serial.println("Passou toggle led");

        const std::string finishRequester = stopRequester.empty() ? requester : stopRequester;
        bool wasInterrupted = !stopRequester.empty();

        MoveFinishedEvent event(finishRequester, parameters, wasInterrupted);
        IoT.notifyEvent(&event);

        moving = false;
        Serial.println("verifica finish callback");
        if (finishCallback)
        {
            AsyncActionFinish result;

            if (wasInterrupted)
            {
                result.setFinishMode(AsyncFinishMode::Abortion);
                result.setAbortionRequester(stopRequester);
            }
            else
            {
                result.setFinishMode(AsyncFinishMode::Normal);
                result.setExecutionRequester(requester);

            }
            Serial.println("antes do finish callback");
            finishCallback(result);
            Serial.println("depois do finish callback");
        }
    }

    void RopeToy::toggleMoveLed(const std::string& requester, MoveParameters parameters, uint8_t state)
    {
        if (parameters.mustTurnOnLed())
        {
            switch (parameters.getDirection())
            {
            case MoveParameters::Direction::Forward:
                leds.front.setState(requester, state);
                return;
            case MoveParameters::Direction::Backward:
                leds.back.setState(requester, state);
                return;
            }
        }
    }

    struct TaskParams {
        Sound* soundPtr;
        std::string requester;
    };

    void moveBackwardTask(void *pvParameters)
    {

        TaskParams* params = static_cast<TaskParams*>(pvParameters);
        Sound* soundPtr = params->soundPtr;
        std::string requester = params->requester;

        soundPtr->play(requester, Note::E, 7, 0.045f, 0.075f, nullptr, nullptr);
        soundPtr->play(requester, Note::D, 7, 0.045f, 0.075f, nullptr, nullptr);
        soundPtr->play(requester, Note::Cs, 7, 0.135f, 0.0f, nullptr, nullptr);
        delete params;
        vTaskDelete(NULL);
    }

    void moveForwardTask(void *pvParameters)
    {
        TaskParams* params = static_cast<TaskParams*>(pvParameters);
        Sound* soundPtr = params->soundPtr;
        std::string requester = params->requester;

        soundPtr->play(requester, Note::Cs, 7, 0.045f, 0.075f, nullptr, nullptr);
        soundPtr->play(requester, Note::D, 7, 0.045f, 0.075f, nullptr, nullptr);
        soundPtr->play(requester, Note::E, 7, 0.135f, 0.0f, nullptr, nullptr);
        delete params;
        vTaskDelete(NULL);
    }

    void RopeToy::playMoveMelody(const std::string& requester, MoveParameters parameters)
    {
        TaskParams* param = new TaskParams{ &sound, requester };
        
        if (parameters.mustPlaySound())
        {
            switch (parameters.getDirection())
            {
            case MoveParameters::Direction::Forward:
                // tocar mover pra frente
                xTaskCreatePinnedToCore(
                    moveForwardTask,
                    "PlaySoundTask",
                    2048,
                    param,
                    1,
                    NULL,
                    1
                );
                return;
            case MoveParameters::Direction::Backward:
                // tocar ir para trás
                xTaskCreatePinnedToCore(
                    moveBackwardTask,
                    "PlaySoundTask",
                    2048,
                    param,
                    1,
                    NULL,
                    1
                );
                return;
            }
        }
    }

    void RopeToy::rotationStarted(const std::string& requester, RotationParameters parameters, AsyncStartCallback startCallback)
    {
        rotating = true;
        stopRequester.clear();

        if (startCallback)
        {
            AsyncActionStart result;
            result.setExecutionRequester(requester);
            startCallback(result);
        }

        RotationStartedEvent event(requester, parameters);
        IoT.notifyEvent(&event);

        toggleRotationLed(requester, parameters, HIGH);
        playRotationMelody(requester, parameters);
    }

    void RopeToy::rotationFinished(const std::string& requester, RotationParameters parameters, AsyncFinishCallback finishCallback)
    {
        toggleRotationLed(requester, parameters, LOW);

        const std::string finishRequester = stopRequester.empty() ? requester : stopRequester;
        bool wasInterrupted = !stopRequester.empty();

        RotationFinishedEvent event(finishRequester, parameters, wasInterrupted);
        IoT.notifyEvent(&event);
        Serial.println("antes callback dentro rotation");
        if (finishCallback)
        {
            AsyncActionFinish result;

            if (wasInterrupted)
            {
                result.setFinishMode(AsyncFinishMode::Abortion);
                result.setAbortionRequester(stopRequester);
            }
            else
            {
                result.setFinishMode(AsyncFinishMode::Normal);
                result.setExecutionRequester(requester);

            }

            finishCallback(result);
        }

        rotating = false;
    }

    void RopeToy::toggleRotationLed(const std::string& requester, RotationParameters parameters, uint8_t state)
    {
        if (parameters.mustTurnOnLed())
        {
            switch (parameters.getDirection())
            {
            case RotationParameters::Direction::Clockwise:
                leds.right.setState(requester, state);
                return;
            case RotationParameters::Direction::CounterClockwise:
                leds.left.setState(requester, state);
                return;
            }
        }
    }

    void turnLeftTask(void *pvParameters)
    {
        TaskParams* params = static_cast<TaskParams*>(pvParameters);
        Sound* soundPtr = params->soundPtr;
        std::string requester = params->requester;

        soundPtr->play(requester, Note::C, 7, 0.045f, 0.050f, nullptr, nullptr);
        soundPtr->play(requester, Note::As, 7, 0.045f, 0.050f, nullptr, nullptr);
        soundPtr->play(requester, Note::A, 7, 0.135f, 0.0f, nullptr, nullptr);
        delete params;
        vTaskDelete(NULL);
    }

    void turnRightTask(void *pvParameters)
    {
        TaskParams* params = static_cast<TaskParams*>(pvParameters);
        Sound* soundPtr = params->soundPtr;
        std::string requester = params->requester;

        soundPtr->play(requester, Note::A, 7, 0.045f, 0.050f, nullptr, nullptr);
        soundPtr->play(requester, Note::As, 7, 0.045f, 0.050f, nullptr, nullptr);
        soundPtr->play(requester, Note::C, 7, 0.135f, 0.0f, nullptr, nullptr);
        delete params;
        vTaskDelete(NULL);
    }

    void RopeToy::playRotationMelody(const std::string& requester, RotationParameters parameters)
    {
        TaskParams* param = new TaskParams{ &sound, requester };
        if (parameters.mustPlaySound())
        {
            switch (parameters.getDirection())
            {
            case RotationParameters::Direction::Clockwise:
                // tocar ir para a direita*
                xTaskCreatePinnedToCore(
                    turnRightTask,
                    "PlaySoundTask",
                    2048,
                    param,
                    1,
                    NULL,
                    1
                );
                return;
            case RotationParameters::Direction::CounterClockwise:
                // tocar ir para a esquerda*
                xTaskCreatePinnedToCore(
                    turnLeftTask,
                    "PlaySoundTask",
                    2048,
                    param,
                    1,
                    NULL,
                    1
                );
                return;
            }
        }
    }

    MoveParameters RopeToy::getDefaultMoveParameters()
    {
        MoveParameters parameters(*this);

        parameters.setDistance(config.moveDistance.get());
        parameters.setSpeed(config.moveSpeed.get());
        parameters.setTurnOnLed(true);
        parameters.setPlaySound(true);
        parameters.setMoveForever(false);
        parameters.setDuration(0.0f);

        return parameters;
    }

    RotationParameters RopeToy::getDefaultRotationParameters()
    {
        RotationParameters parameters(*this);

        parameters.setDegrees(90.0f);
        parameters.setSpeed(config.rotationSpeed.get());
        parameters.setTurnOnLed(true);
        parameters.setPlaySound(true);
        parameters.setRotateForever(false);
        parameters.setDuration(0.0f);

        return parameters;
    }

    void RopeToy::stop(const std::string& requester)
    {
        if (moving || rotating)
        {
            stopRequester = requester;

            motors.stop();
            sound.stop(requester);
            moving = false;
            rotating = false;
        }
    }

    bool RopeToy::cantMoveOrRotate() const
    {
        if (moving || rotating)
        {
            // h4pUserEvent(ERROR_PREFIX " will not move or rotate, the robot is already %s", moving ? "moving" : "rotating");
            return true;
        }

        return false;
    }

    void errorSoundTask(void *pvParameters)
    {
        TaskParams* params = static_cast<TaskParams*>(pvParameters);
        Sound* soundPtr = params->soundPtr;
        std::string requester = params->requester;

        soundPtr->play(requester, Note::E, 7, 0.045f, 0.050f, nullptr, nullptr);
        soundPtr->play(requester, Note::D, 7, 0.045f, 0.050f, nullptr, nullptr);
        soundPtr->play(requester, Note::C, 7, 0.045f, 0.50f, nullptr, nullptr);
        soundPtr->play(requester, Note::Bb, 6, 0.135f, 0.0f, nullptr, nullptr);

        delete params;
        vTaskDelete(NULL);
    }

    void RopeToy::playErrorFeedback()
    {
        TaskParams* param = new TaskParams{ &sound, Event::Origin::User };
        leds.cycle(100);
        // tocar erro
        xTaskCreatePinnedToCore(
            errorSoundTask,
            "PlaySoundTask",
            2048,
            param,
            1,
            NULL,
            1
        );
    }
} // namespace Rope
