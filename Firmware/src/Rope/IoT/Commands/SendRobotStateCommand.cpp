#include "Rope/IoT/Commands/SendRobotStateCommand.hpp"

#include <string>
#include "Rope/RopeToy.hpp"
#include "Rope/IoT/Events/RobotStateEvent.hpp"

namespace Rope
{
    SendRobotStateCommand::SendRobotStateCommand(RopeToy& rope) : Command("SEND_ROBOT_STATE", rope)
    {
    }

    bool SendRobotStateCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        RobotStateEvent event(requester, rope);
        rope.IoT.notifyEvent(&event);

        return true;
    }
}