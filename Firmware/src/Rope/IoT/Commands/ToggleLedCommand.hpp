#ifndef ROPE_TOGGLE_LED_COMMAND_HPP
#define ROPE_TOGGLE_LED_COMMAND_HPP

#include "Rope/IoT/Command.hpp"

namespace Rope
{
    class ToggleLedCommand : public Command
    {
    public:
        ToggleLedCommand(RopeToy& rope);

        bool execute(const std::string& requester, const JsonObject& parameters) const;
    };
}

#endif // ROPE_TOGGLE_LED_COMMAND_HPP