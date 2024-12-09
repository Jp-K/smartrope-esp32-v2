#ifndef ROPE_IOT_RESIZE_MEMORY_COMMAND_HPP
#define ROPE_IOT_RESIZE_MEMORY_COMMAND_HPP

#include "Rope/IoT/Command.hpp"

namespace Rope
{
    class ResizeMemoryCommand : public Command
    {
    public:
        ResizeMemoryCommand(RopeToy& rope);

        bool execute(const std::string& requester, const JsonObject& parameters) const;
    };
}

#endif // ROPE_IOT_RESIZE_MEMORY_COMMAND_HPP