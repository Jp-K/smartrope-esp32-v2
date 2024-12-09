#ifndef ROPE_IOT_TUNE_MOTORS_COMMAND_HPP
#define ROPE_IOT_TUNE_MOTORS_COMMAND_HPP

#include "Rope/IoT/Command.hpp"

namespace Rope
{
    class TuneMotorsCommand : public Command
    {
    public:
        TuneMotorsCommand(RopeToy& rope);

        bool execute(const std::string& requester, const JsonObject& parameters) const;
    };
}

#endif // ROPE_IOT_TUNE_MOTORS_COMMAND_HPP