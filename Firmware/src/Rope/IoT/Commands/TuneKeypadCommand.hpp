#ifndef ROPE_IOT_TUNE_KEYPAD_COMMAND_HPP
#define ROPE_IOT_TUNE_KEYPAD_COMMAND_HPP

#include "Rope/IoT/Command.hpp"

namespace Rope
{
    class TuneKeypadCommand : public Command
    {
    public:
        TuneKeypadCommand(RopeToy& rope);

        bool execute(const std::string& requester, const JsonObject& parameters) const;
    };
}

#endif // ROPE_IOT_TUNE_KEYPAD_COMMAND_HPP