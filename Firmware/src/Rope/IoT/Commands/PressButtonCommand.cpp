#include "Rope/IoT/Commands/PressButtonCommand.hpp"

#include <string>
#include "Rope/RopeToy.hpp"

namespace Rope
{
    PressButtonCommand::PressButtonCommand(RopeToy& rope) : Command("PRESS_BUTTON", rope)
    {
    }

    bool PressButtonCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        std::string buttonName = parameters["button"] | "NULL";
        auto button = rope.keypad.buttons.withName(buttonName);

        if (button)
        {
            button->press(requester, rope);
            return true;
        }

        // h4pUserEvent("%s: invalid button \"%s\"", getName().c_str(), buttonName.c_str());
        return false;
    }
}