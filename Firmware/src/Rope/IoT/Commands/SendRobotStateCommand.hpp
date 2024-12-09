#ifndef ROPE_IOT_SEND_ROBOT_STATE_COMMAND_HPP
#define ROPE_IOT_SEND_ROBOT_STATE_COMMAND_HPP

#include "Rope/IoT/Command.hpp"

namespace Rope
{
    class SendRobotStateCommand : public Command
    {
    public:
        SendRobotStateCommand(RopeToy& rope);

        bool execute(const std::string& requester, const JsonObject& parameters) const;
    };
}

#endif // ROPE_IOT_SEND_ROBOT_STATE_COMMAND_HPP