#ifndef ROPE_IOT_MOVE_COMMAND_HPP
#define ROPE_IOT_MOVE_COMMAND_HPP

#include "Rope/IoT/Command.hpp"

namespace Rope
{
    class MoveCommand : public Command
    {
    public:
        MoveCommand(RopeToy& rope);

        bool execute(const std::string& requester, const JsonObject& parameters) const;
    };
}

#endif // ROPE_IOT_MOVE_COMMAND_HPP