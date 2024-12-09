#ifndef ROPE_TOGGLE_PIN_COMMAND_HPP
#define ROPE_TOGGLE_PIN_COMMAND_HPP

#include "Rope/IoT/Command.hpp"

namespace Rope
{
    class TogglePinCommand : public Command
    {
    public:
        TogglePinCommand(RopeToy& rope);

        bool execute(const std::string& requester, const JsonObject& parameters) const;
    };
}

#endif // ROPE_TOGGLE_PIN_COMMAND_HPP