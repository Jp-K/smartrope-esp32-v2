#include "Rope/IoT/Commands/InsertInstructionCommand.hpp"

#include <string>
#include "Rope/RopeToy.hpp"

namespace Rope
{
    InsertInstructionCommand::InsertInstructionCommand(RopeToy& rope) : Command("INSERT_INSTRUCTION", rope)
    {
    }

    bool InsertInstructionCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        std::string instructionName = parameters["instruction"] | "NULL";
        int32_t index = parameters["index"] | -1;

        auto instruction = rope.program.instructions.withName(instructionName);

        if (instruction)
        {
            if (index >= 0)
            {
                rope.program.insertInstruction(requester, *instruction, index);
            }
            else
            {
                rope.program.insertInstruction(requester, *instruction);
            }

            return true;
        }

        // h4pUserEvent("%s: invalid instruction \"%s\"", getName().c_str(), instructionName.c_str());
        return false;
    }
}