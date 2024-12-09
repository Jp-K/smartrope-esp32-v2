#include "Rope/IoT/Commands/TogglePinCommand.hpp"

#include "Rope/RopeToy.hpp"

namespace Rope
{
    TogglePinCommand::TogglePinCommand(RopeToy& rope) : Command("TOGGLE_PIN", rope)
    {

    }

    bool TogglePinCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        uint8_t pin = parameters["pin"] | 255;
        std::string state = parameters["state"] | "null";

        if (state != "ON" && state != "OFF")
        {
            // h4pUserEvent("Invalid state: \"%s\"", state.c_str());
            return false;
        }

        if (pin == 255)
        {
            // h4pUserEvent("Invalid pin: %d", pin);
            return false;
        }

        pinMode(pin, OUTPUT);
        digitalWrite(pin, state == "ON" ? HIGH : LOW);

        // h4pUserEvent("Pin %d turned %s", pin, state.c_str());

        return true;
    }
}