#ifndef ROPE_IOT_PRESS_BUTTON_COMMAND_HPP
#define ROPE_IOT_PRESS_BUTTON_COMMAND_HPP

#include "Rope/IoT/Command.hpp"

namespace Rope
{
    class PressButtonCommand : public Command
    {
    public:
        PressButtonCommand(RopeToy& rope);

        bool execute(const std::string& requester, const JsonObject& parameters) const;
    };
}

#endif // ROPE_IOT_PRESS_BUTTON_COMMAND_HPP