#ifndef ROPE_IOT_EXECUTE_PROGRAM_COMMAND_HPP
#define ROPE_IOT_EXECUTE_PROGRAM_COMMAND_HPP

#include "Rope/IoT/Command.hpp"

namespace Rope
{
    class ExecuteProgramCommand : public Command
    {
    public:
        ExecuteProgramCommand(RopeToy& rope);

        bool execute(const std::string& requester, const JsonObject& parameters) const;
    };
}

#endif // ROPE_IOT_EXECUTE_PROGRAM_COMMAND_HPP