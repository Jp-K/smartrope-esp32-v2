#include "Rope/Keypad/Buttons/RightButton.hpp"

#include "Rope/RopeToy.hpp"

namespace Rope
{
    RightButton::RightButton() : Button("RIGHT", Range(1700, 1800))
    {

    }

    struct TaskParams {
        RopeToy* ropePtr;
    };

    void playSoundTaskRight(void *pvParameters) {

        TaskParams* params = static_cast<TaskParams*>(pvParameters);
        RopeToy* ropePtr = params->ropePtr;

        // tocar botão da direita
        ropePtr->sound.play(Event::Origin::Rope, Note::B, 7, 0.045f, 0.0f);

        delete params;
        // Apaga a task depois que a melodia foi tocada uma vez
        vTaskDelete(NULL);
    }

    void RightButton::onPress(const std::string& requester, RopeToy& rope)
    {
        if (rope.program.insertInstruction(requester, rope.program.instructions.rotateClockwise))
        {
            rope.leds.right.blinkOnce(Event::Origin::Rope, 45);
            // tocar botão direito
            TaskParams* param = new TaskParams{ &rope };
            xTaskCreatePinnedToCore(
                playSoundTaskRight,
                "PlaySoundTaskRight",
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