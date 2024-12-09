#include "Rope/IoT/Commands/ClearMemoryCommand.hpp"

#include <string>
#include "Rope/RopeToy.hpp"

namespace Rope
{
    ClearMemoryCommand::ClearMemoryCommand(RopeToy& rope) : Command("CLEAR_MEMORY", rope)
    {
    }

    bool ClearMemoryCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        rope.program.clear(requester);
        return true;
    }
}