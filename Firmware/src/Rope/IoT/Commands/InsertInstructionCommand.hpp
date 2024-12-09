#ifndef ROPE_IOT_INSERT_INSTRUCTION_COMMAND_HPP
#define ROPE_IOT_INSERT_INSTRUCTION_COMMAND_HPP

#include "Rope/IoT/Command.hpp"

namespace Rope
{
    class InsertInstructionCommand : public Command
    {
    public:
        InsertInstructionCommand(RopeToy& rope);

        bool execute(const std::string& requester, const JsonObject& parameters) const;
    };
}

#endif // ROPE_IOT_INSERT_INSTRUCTION_COMMAND_HPP