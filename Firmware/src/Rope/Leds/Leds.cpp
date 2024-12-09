#include "Rope/Leds/Leds.hpp"

#include "Rope/RopeToy.hpp"

namespace Rope
{
    Leds::Leds(RopeToy& rope) : NamedEntityContainer("Leds"),
        front(rope, "FRONT", rope.pins.frontLed),
        right(rope, "RIGHT", rope.pins.rightLed),
        back(rope, "BACK", rope.pins.backLed),
        left(rope, "LEFT", rope.pins.leftLed),
        center(rope, "CENTER", rope.pins.centerLed)
    {
        addEntity(front);
        addEntity(right);
        addEntity(back);
        addEntity(left);
        addEntity(center);
    }

    //void Leds::cycle(uint32_t intervalOn) const
    //{
    //    uint8_t index = 0;

    //    for (auto led : all())
    //    {
    //        if (led == &center)
    //        {
    //            continue;
    //        }

    //        uint32_t duration = 1 + (intervalOn * index);
    //        h4.once(duration, [led, intervalOn](){ led->blinkOnce("ROPE", intervalOn); });

    //        index++;
    //    }
    //}

    struct BlinkLedTaskParams
    {
        Led* led;
        uint32_t duration;
        uint32_t intervalOn;
    };

    void blinkLedTask(void *param)
    {

        BlinkLedTaskParams* params = static_cast<BlinkLedTaskParams*>(param);

        vTaskDelay(params->duration / portTICK_PERIOD_MS);
        params->led->blinkOnce("ROPE", params->intervalOn);
        vTaskDelete(NULL);
    }

    void Leds::cycle(uint32_t intervalOn) const
    {
        uint8_t index = 0;

        for (auto led : all())
        {
            if (led == &center)
            {
                continue;
            }

            uint32_t duration = 1 + (intervalOn * index);

            BlinkLedTaskParams* params = new BlinkLedTaskParams{led, duration, intervalOn};

            xTaskCreatePinnedToCore(
                blinkLedTask,               
                "BlinkLedTask",        
                2048,                    
                params,              
                1,                        
                NULL,                 
                1                           
            );

            index++;
        }
    }
}