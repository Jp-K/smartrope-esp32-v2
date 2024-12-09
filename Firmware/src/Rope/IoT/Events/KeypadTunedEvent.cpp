#include "Rope/IoT/Events/KeypadTunedEvent.hpp"

namespace Rope
{
    KeypadTunedEvent::KeypadTunedEvent(const std::string& origin, const KeypadParameters& parameters, bool keypadIsOn) :
        Event("KEYPAD_TUNED", origin),
        parameters(parameters),
        keypadIsOn(keypadIsOn)
    {

    }

    void KeypadTunedEvent::fillData(const JsonObject& data) const
    {
        data["state"] = keypadIsOn ? "ON" : "OFF";
        data["debounceInterval"] = parameters.getDebounceInterval();
        data["updateInterval"] = parameters.getUpdateInterval();
    }
}