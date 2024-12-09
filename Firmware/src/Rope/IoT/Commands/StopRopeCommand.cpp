#include "Rope/IoT/Commands/StopRopeCommand.hpp"

#include <string>
#include "Rope/RopeToy.hpp"

namespace Rope
{
    StopRopeCommand::StopRopeCommand(RopeToy& rope) : Command("STOP_ROPE", rope)
    {

    }

    bool StopRopeCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        rope.stop(requester);
        return true;
    }
}