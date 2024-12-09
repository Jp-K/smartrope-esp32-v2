#ifndef ROPE_SET_GPIO_REGISTER_COMMAND_HPP
#define ROPE_SET_GPIO_REGISTER_COMMAND_HPP

#include "Rope/IoT/Command.hpp"

namespace Rope
{
    class SetGPIORegisterCommand : public Command
    {
    public:
        SetGPIORegisterCommand(RopeToy& rope);

        bool execute(const std::string& requester, const JsonObject& parameters) const;
    };
}

#endif // ROPE_SET_GPIO_REGISTER_COMMAND_HPP