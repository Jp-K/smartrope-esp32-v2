#include "Rope/Keypad/Buttons/FrontButton.hpp"

#include "Rope/RopeToy.hpp"

namespace Rope
{
    FrontButton::FrontButton() : Button("FRONT", Range(1300, 1400))
    {

    }

    struct TaskParams {
        RopeToy* ropePtr;
    };

    void playSoundTaskFront(void *pvParameters) {

        TaskParams* params = static_cast<TaskParams*>(pvParameters);
        RopeToy* ropePtr = params->ropePtr;

        // tocar botão da frente
        ropePtr->sound.play(Event::Origin::Rope, Note::Cs, 7, 0.045f, 0.0f);

        delete params;
        // Apaga a task depois que a melodia foi tocada uma vez
        vTaskDelete(NULL);
    }

    void FrontButton::onPress(const std::string& requester, RopeToy& rope)
    {
        if (rope.program.insertInstruction(requester, rope.program.instructions.moveForward))
        {
            rope.leds.front.blinkOnce(Event::Origin::Rope, 45);
            // tocar botão da frente

            TaskParams* param = new TaskParams{ &rope };
            xTaskCreatePinnedToCore(
                playSoundTaskFront,
                "PlaySoundTaskFront",
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