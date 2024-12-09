#ifndef ROPE_IOT_CLEAR_MEMORY_COMMAND_HPP
#define ROPE_IOT_CLEAR_MEMORY_COMMAND_HPP

#include "Rope/IoT/Command.hpp"

namespace Rope
{
    class ClearMemoryCommand : public Command
    {
    public:
        ClearMemoryCommand(RopeToy& rope);

        bool execute(const std::string& requester, const JsonObject& parameters) const;
    };
}

#endif // ROPE_IOT_CLEAR_MEMORY_COMMAND_HPP