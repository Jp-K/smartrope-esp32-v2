#ifndef ROPE_IOT_STOP_ROPE_COMMAND_HPP
#define ROPE_IOT_STOP_ROPE_COMMAND_HPP

#include "Rope/IoT/Command.hpp"

namespace Rope
{
    class StopRopeCommand : public Command
    {
    public:
        StopRopeCommand(RopeToy& rope);

        bool execute(const std::string& requester, const JsonObject& parameters) const;
    };
}

#endif // ROPE_IOT_STOP_ROPE_COMMAND_HPP