#include "Rope/IoT/Commands/TuneSoundCommand.hpp"

#include "Rope/RopeToy.hpp"
#include "Rope/Sound/PlaybackParameters.hpp"
namespace Rope
{
    TuneSoundCommand::TuneSoundCommand(RopeToy& rope) : Command("TUNE_SOUND", rope)
    {

    }

    bool TuneSoundCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        PlaybackParameters playbackParameters = rope.sound.getDefaultPlaybackParameters();

        std::string state = parameters["state"] | (rope.sound.isOn() ? "ON" : "OFF");
        uint16_t tempo = parameters["tempo"] | playbackParameters.getTempo();
        uint8_t volume = parameters["volume"] | playbackParameters.getVolume();
        int8_t transposition = parameters["transposition"] | playbackParameters.getTransposition();

        playbackParameters.setTempo(tempo);
        playbackParameters.setVolume(volume);
        playbackParameters.setTransposition(transposition);

        if (state == "ON")
        {
            rope.sound.turnOn(requester);
        }
        else if (state == "OFF")
        {
            rope.sound.turnOff(requester);
        }

        rope.sound.setDefaultPlaybackParameters(requester, playbackParameters);

        return true;
    }
}