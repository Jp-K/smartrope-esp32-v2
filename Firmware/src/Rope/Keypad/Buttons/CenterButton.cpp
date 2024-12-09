#include "Rope/Keypad/Buttons/CenterButton.hpp"

#include "Rope/RopeToy.hpp"

namespace Rope
{
    CenterButton::CenterButton() : Button("CENTER", Range(3850, 3950))
    {

    }

    struct TaskParams {
        RopeToy* ropePtr;
    };

    void playSoundTaskCenter(void *pvParameters) {
        // tocar botão do meio
        TaskParams* params = static_cast<TaskParams*>(pvParameters);
        RopeToy* ropePtr = params->ropePtr;
        // AsyncFinishCallback afterSound = [&ropePtr](AsyncActionFinish result)
        // {
        //     Serial.println("entrou no after sound");
        //     if (ropePtr != nullptr) {
        //         ropePtr->program.execute(Event::Origin::Rope, nullptr, nullptr);
        //     } else {
        //         Serial.println("ropePtr é inválido");
        //     }
        // };
        Serial.println("antes do play sound");
        ropePtr->sound.play(Event::Origin::Rope, Note::D, 7, 0.045f, 0.0f, nullptr, nullptr);
        ropePtr->program.execute(Event::Origin::Rope, nullptr, nullptr);

        delete params;
        // Apaga a task depois que a melodia foi tocada uma vez
        //vTaskDelete(NULL);
    }

    void CenterButton::onPress(const std::string& requester, RopeToy& rope)
    {
        if (rope.program.isExecuting())
        {
            rope.program.abort(requester);
            return;
        }

        if (rope.program.isEmpty())
        {
            rope.playErrorFeedback();
            return;
        }

        rope.leds.center.blinkOnce(Event::Origin::Rope, 45);
        // tocar botão do centro
        TaskParams* param = new TaskParams{ &rope };
        // xTaskCreatePinnedToCore(
        //     playSoundTaskCenter,
        //     "PlaySoundTaskCenter",
        //     8192,
        //     param,
        //     1,
        //     NULL,
        //     1
        // );
        playSoundTaskCenter(param);
    }
}