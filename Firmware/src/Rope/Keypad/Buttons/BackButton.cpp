#include "Rope/Keypad/Buttons/BackButton.hpp"

#include "Rope/RopeToy.hpp"

namespace Rope
{
    BackButton::BackButton() : Button("BACK", Range(2050, 2150))
    {

    }

    struct TaskParams {
        RopeToy* ropePtr;
    };

    void playSoundTaskBack(void *pvParameters) {

        TaskParams* params = static_cast<TaskParams*>(pvParameters);
        RopeToy* ropePtr = params->ropePtr;

        // tocar botão de trás
        ropePtr->sound.play(Event::Origin::Rope, Note::E, 7, 0.045f, 0.0f);

        delete params;
        // Apaga a task depois que a melodia foi tocada uma vez
        vTaskDelete(NULL);
    }

    void BackButton::onPress(const std::string& requester, RopeToy& rope)
    {
        if (rope.program.insertInstruction(requester, rope.program.instructions.moveBackward))
        {
            rope.leds.back.blinkOnce(Event::Origin::Rope, 45);

            TaskParams* param = new TaskParams{ &rope };
            xTaskCreatePinnedToCore(
                playSoundTaskBack,
                "PlaySoundTaskBack",
                2048,
                param,
                1,
                NULL,
                1
            );

            return;
        }

        rope.playErrorFeedback();
    }
}