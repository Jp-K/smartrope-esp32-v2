#ifndef ROPE_IOT_SOUND_TUNED_EVENT_HPP
#define ROPE_IOT_SOUND_TUNED_EVENT_HPP

#include "Rope/IoT/Event.hpp"
#include "Rope/Sound/PlaybackParameters.hpp"

namespace Rope
{
    class SoundTunedEvent : public Event
    {
    private:
        bool soundIsOn;
        PlaybackParameters parameters;

    public:
        SoundTunedEvent(const std::string& origin, const PlaybackParameters& parameters, bool soundIsOn);
        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_SOUND_TUNED_EVENT_HPP