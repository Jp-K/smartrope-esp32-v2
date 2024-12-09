#include "Rope/IoT/Commands/ToggleLedCommand.hpp"

#include "Rope/RopeToy.hpp"

namespace Rope
{
    ToggleLedCommand::ToggleLedCommand(RopeToy& rope) : Command("TOGGLE_LED", rope)
    {

    }

    bool ToggleLedCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        std::string ledName = parameters["led"] | "null";
        std::string state = parameters["state"] | "null";

        if (state != "ON" && state != "OFF")
        {
            // h4pUserEvent("Invalid state: \"%s\"", state.c_str());
            return false;
        }

        auto led = rope.leds.withName(ledName);

        if (led)
        {
            led->setState(requester, state == "ON" ? HIGH : LOW);
            return true;
        }

        // h4pUserEvent("Led \"%s\" not found", ledName.c_str());
        return false;
    }
}