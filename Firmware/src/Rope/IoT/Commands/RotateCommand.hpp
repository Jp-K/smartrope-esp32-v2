#ifndef ROPE_IOT_ROTATE_COMMAND_HPP
#define ROPE_IOT_ROTATE_COMMAND_HPP

#include "Rope/IoT/Command.hpp"

namespace Rope
{
    class RotateCommand : public Command
    {
    public:
        RotateCommand(RopeToy& rope);

        bool execute(const std::string& requester, const JsonObject& parameters) const;
    };
}

#endif // ROPE_IOT_ROTATE_COMMAND_HPP