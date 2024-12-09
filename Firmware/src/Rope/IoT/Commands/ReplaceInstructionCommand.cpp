#include "Rope/IoT/Commands/ReplaceInstructionCommand.hpp"

#include <string>
#include "Rope/RopeToy.hpp"

namespace Rope
{
    ReplaceInstructionCommand::ReplaceInstructionCommand(RopeToy& rope) : Command("REPLACE_INSTRUCTION", rope)
    {
    }

    bool ReplaceInstructionCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        std::string instructionName = parameters["instruction"] | "NULL";
        int32_t index = parameters["index"] | -1;

        auto instruction = rope.program.instructions.withName(instructionName);

        if (instruction)
        {
            if (index >= 0)
            {
                rope.program.replaceInstruction(requester, *instruction, index);
                return true;
            }
            else
            {
                rope.program.replaceInstruction(requester, *instruction);
            }

            return false;
        }

        // h4pUserEvent("%s: invalid instruction \"%s\"", getName().c_str(), instructionName.c_str());
        return false;
    }
}