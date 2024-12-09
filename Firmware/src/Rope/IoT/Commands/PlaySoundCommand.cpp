#include "Rope/IoT/Commands/PlaySoundCommand.hpp"

#include "Rope/RopeToy.hpp"
#include "Rope/Sound/PlaybackParameters.hpp"

namespace Rope
{
    PlaySoundCommand::PlaySoundCommand(RopeToy& rope) : Command("PLAY_SOUND", rope)
    {

    }

    bool PlaySoundCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        PlaybackParameters playbackParameters = rope.sound.getDefaultPlaybackParameters();

        std::string melody = parameters["melody"];
        bool playForever = parameters["forever"] | false;
        uint8_t repetitions = parameters["repetitions"] | 1;
        int16_t transposition = parameters["transposition"] | playbackParameters.getTransposition();
        uint8_t volume = parameters["volume"] | playbackParameters.getVolume();
        uint16_t tempo = parameters["tempo"] | playbackParameters.getTempo();

        playbackParameters.setPlayForever(playForever);
        playbackParameters.setRepetitions(repetitions);
        playbackParameters.setTransposition(transposition);
        playbackParameters.setVolume(volume);
        playbackParameters.setTempo(tempo);

        if (melody.length() > 0)
        {
            // tocar som genérico (descobrir como fazer isso aqui ainda)
            // rope.sound.play(requester, melody, playbackParameters);
            
            return true;
        }

        return false;
    }
}