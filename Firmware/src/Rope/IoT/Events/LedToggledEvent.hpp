#ifndef ROPE_IOT_LED_TOGGLED_EVENT
#define ROPE_IOT_LED_TOGGLED_EVENT

#include "Rope/IoT/Event.hpp"
#include "Rope/Leds/Led.hpp"

namespace Rope
{
    class LedToggledEvent : public Event
    {
    private:
        Led* led;

    public:
        LedToggledEvent(const std::string& origin, Led* led);
        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_LED_TOGGLED_EVENT