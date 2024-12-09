#include "Rope/Keypad/Buttons/LeftButton.hpp"

#include "Rope/RopeToy.hpp"

namespace Rope
{
    LeftButton::LeftButton() : Button("LEFT", Range(2350, 2450))
    {

    }

    struct TaskParams {
        RopeToy* ropePtr;
    };

    void playSoundTaskLeft(void *pvParameters) {

        TaskParams* params = static_cast<TaskParams*>(pvParameters);
        RopeToy* ropePtr = params->ropePtr;
        // tocar botão da esquerda
        ropePtr->sound.play(Event::Origin::Rope, Note::C, 7, 0.045f, 0.0f);

        delete params;
        // Apaga a task depois que a melodia foi tocada uma vez
        vTaskDelete(NULL);
    }

    void LeftButton::onPress(const std::string& requester, RopeToy& rope)
    {
        if (rope.program.insertInstruction(requester, rope.program.instructions.rotateCounterClockwise))
        {
            rope.leds.left.blinkOnce(Event::Origin::Rope, 45);
            // tocar botão esquerdo
            TaskParams* param = new TaskParams{ &rope };
            xTaskCreatePinnedToCore(
                playSoundTaskLeft,
                "PlaySoundTaskLeft",
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