#include "Rope/IoT/Commands/TuneKeypadCommand.hpp"

#include <string>

#include "Rope/RopeToy.hpp"
#include "Rope/Keypad/KeypadParameters.hpp"

namespace Rope
{
    TuneKeypadCommand::TuneKeypadCommand(RopeToy& rope) : Command("TUNE_KEYPAD", rope)
    {
    }

    bool TuneKeypadCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        KeypadParameters keypadParameters = rope.keypad.getKeypadParameters();

        std::string state = parameters["state"] | (rope.keypad.isOn() ? "ON" : "OFF");
        uint32_t debounceInterval = parameters["debounceInterval"] | keypadParameters.getDebounceInterval();
        uint32_t updateInterval = parameters["updateInterval"] | keypadParameters.getUpdateInterval();

        keypadParameters.setDebounceInterval(debounceInterval);
        keypadParameters.setUpdateInterval(updateInterval);

        if (state == "ON")
        {
            rope.keypad.turnOn(requester);
        }
        else if (state == "OFF")
        {
            rope.keypad.turnOff(requester);
        }

        rope.keypad.setKeypadParameters(requester, keypadParameters);

        return true;
    }
}