#include "Rope/IoT/Commands/RemoveInstructionCommand.hpp"

#include <string>
#include "Rope/RopeToy.hpp"

namespace Rope
{
    RemoveInstructionCommand::RemoveInstructionCommand(RopeToy& rope) : Command("REMOVE_INSTRUCTION", rope)
    {
    }

    bool RemoveInstructionCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        int32_t index = parameters["index"] | -1;

        if (index >= 0)
        {
            rope.program.removeInstruction(requester, index);
        }
        else
        {
            rope.program.removeInstruction(requester);
        }
        
        return true;
    }
}