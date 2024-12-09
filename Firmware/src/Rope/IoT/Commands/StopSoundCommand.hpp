#ifndef ROPE_STOP_SOUND_COMMAND_HPP
#define ROPE_STOP_SOUND_COMMAND_HPP

#include "Rope/IoT/Command.hpp"

namespace Rope
{
    class StopSoundCommand : public Command
    {
    public:
        StopSoundCommand(RopeToy& rope);

        bool execute(const std::string& requester, const JsonObject& parameters) const;
    };
}

#endif // ROPE_STOP_SOUND_COMMAND_HPP