#include "Rope/IoT/Commands/StopSoundCommand.hpp"

#include "Rope/RopeToy.hpp"

namespace Rope
{
    StopSoundCommand::StopSoundCommand(RopeToy& rope) : Command("STOP_SOUND", rope)
    {

    }

    bool StopSoundCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        rope.sound.stop(requester);
        return true;
    }
}