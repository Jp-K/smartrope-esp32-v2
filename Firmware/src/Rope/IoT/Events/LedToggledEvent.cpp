#include "Rope/IoT/Events/LedToggledEvent.hpp"

namespace Rope
{
    LedToggledEvent::LedToggledEvent(const std::string& origin, Led* led) :
        Event("LED_TOGGLED", origin),
        led(led)
    {

    }

    void LedToggledEvent::fillData(const JsonObject& data) const
    {
        data["led"] = led->getName();
        data["state"] = led->isOn() ? "ON" : "OFF";
    }
}