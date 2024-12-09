#include "Rope/IoT/Events/SoundPlaybackFinishedEvent.hpp"

namespace Rope
{
    SoundPlaybackFinishedEvent::SoundPlaybackFinishedEvent(const std::string& origin, const std::string& melody, const PlaybackParameters& parameters, uint32_t playbackIndex, bool wasInterrupted) :
        Event("SOUND_PLAYBACK_FINISHED", origin),
        melody(melody),
        parameters(parameters),
        playbackIndex(playbackIndex),
        wasInterrupted(wasInterrupted)
    {

    }

    void SoundPlaybackFinishedEvent::fillData(const JsonObject& data) const
    {
        data["index"] = playbackIndex;
        data["melody"] = melody;
        data["volume"] = parameters.getVolume();
        data["tempo"] = parameters.getTempo();
        data["repetitions"] = parameters.getRepetitions();
        data["transposition"] = parameters.getTransposition();
        data["forever"] = parameters.mustPlayForever();
        data["finishMode"] = wasInterrupted ? "ABORTED" : "NORMAL";
    }
}