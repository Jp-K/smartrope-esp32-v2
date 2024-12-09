#include "Rope/IoT/Commands/ResizeMemoryCommand.hpp"

#include <string>
#include "Rope/RopeToy.hpp"

namespace Rope
{
    ResizeMemoryCommand::ResizeMemoryCommand(RopeToy& rope) : Command("RESIZE_MEMORY", rope)
    {
    }

    bool ResizeMemoryCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        uint16_t size = parameters["size"] | 0;

        if (size > 0)
        {
            rope.program.resize(requester, size);
            return true;
        }

        return false;
    }
}