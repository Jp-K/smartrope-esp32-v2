#include "Rope/IoT/Events/SoundTunedEvent.hpp"

namespace Rope
{
    SoundTunedEvent::SoundTunedEvent(const std::string& origin, const PlaybackParameters& parameters, bool soundIsOn) :
        Event("SOUND_TUNED", origin),
        parameters(parameters),
        soundIsOn(soundIsOn)
    {

    }

    void SoundTunedEvent::fillData(const JsonObject& data) const
    {
        data["state"] = soundIsOn ? "ON" : "OFF";
        data["volume"] = parameters.getVolume();
        data["tempo"] = parameters.getTempo();
        data["transposition"] = parameters.getTransposition();
    }
}