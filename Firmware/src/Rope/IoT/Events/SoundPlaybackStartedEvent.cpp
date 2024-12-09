#include "Rope/IoT/Events/SoundPlaybackStartedEvent.hpp"

namespace Rope
{
    SoundPlaybackStartedEvent::SoundPlaybackStartedEvent(const std::string& origin, const std::string& melody, const PlaybackParameters& parameters, uint32_t playbackIndex) :
        Event("SOUND_PLAYBACK_STARTED", origin),
        melody(melody),
        parameters(parameters),
        playbackIndex(playbackIndex)
    {

    }

    void SoundPlaybackStartedEvent::fillData(const JsonObject& data) const
    {
        data["index"] = playbackIndex;
        data["melody"] = melody;
        data["volume"] = parameters.getVolume();
        data["tempo"] = parameters.getTempo();
        data["repetitions"] = parameters.getRepetitions();
        data["transposition"] = parameters.getTransposition();
        data["forever"] = parameters.mustPlayForever();
    }
}