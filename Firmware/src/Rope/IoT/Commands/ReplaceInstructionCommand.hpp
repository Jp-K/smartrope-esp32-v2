#ifndef ROPE_IOT_REPLACE_INSTRUCTION_COMMAND_HPP
#define ROPE_IOT_REPLACE_INSTRUCTION_COMMAND_HPP

#include "Rope/IoT/Command.hpp"

namespace Rope
{
    class ReplaceInstructionCommand : public Command
    {
    public:
        ReplaceInstructionCommand(RopeToy& rope);

        bool execute(const std::string& requester, const JsonObject& parameters) const;
    };
}

#endif // ROPE_IOT_REPLACE_INSTRUCTION_COMMAND_HPP