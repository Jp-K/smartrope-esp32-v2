#ifndef ROPE_TUNE_SOUND_COMMAND_HPP
#define ROPE_TUNE_SOUND_COMMAND_HPP

#include "Rope/IoT/Command.hpp"

namespace Rope
{
    class TuneSoundCommand : public Command
    {
    public:
        TuneSoundCommand(RopeToy& rope);

        bool execute(const std::string& requester, const JsonObject& parameters) const;
    };
}

#endif // ROPE_TUNE_SOUND_COMMAND_HPP