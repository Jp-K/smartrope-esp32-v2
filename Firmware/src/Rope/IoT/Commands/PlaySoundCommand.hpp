#ifndef ROPE_PLAY_SOUND_COMMAND_HPP
#define ROPE_PLAY_SOUND_COMMAND_HPP

#include "Rope/IoT/Command.hpp"

namespace Rope
{
    class PlaySoundCommand : public Command
    {
    public:
        PlaySoundCommand(RopeToy& rope);

        bool execute(const std::string& requester, const JsonObject& parameters) const;
    };
}

#endif // ROPE_PLAY_SOUND_COMMAND_HPP