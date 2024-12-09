#ifndef ROPE_IOT_SOUND_PLAYBACK_FINISHED_EVENT_HPP
#define ROPE_IOT_SOUND_PLAYBACK_FINISHED_EVENT_HPP

#include "Rope/IoT/Event.hpp"
#include "Rope/Sound/PlaybackParameters.hpp"

namespace Rope
{
    class SoundPlaybackFinishedEvent : public Event
    {
    private:
        uint32_t playbackIndex;
        std::string melody;
        PlaybackParameters parameters;
        bool wasInterrupted;

    public:
        SoundPlaybackFinishedEvent(const std::string& origin, const std::string& melody, const PlaybackParameters& parameters, uint32_t playbackIndex, bool wasInterrupted);
        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_SOUND_PLAYBACK_FINISHED_EVENT_HPP