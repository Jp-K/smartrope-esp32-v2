#include "Rope/Sound/PlaybackParameters.hpp"

#include "Rope/RopeToy.hpp"
#include "Rope/Util/Value.hpp"

namespace Rope
{
    PlaybackParameters::PlaybackParameters(RopeToy& rope) : rope(rope)
    {
        setTempo(60);
        setVolume(8);
        setRepetitions(1);
        setTransposition(0);
        setPlayForever(false);
    }

    uint16_t PlaybackParameters::getTempo() const
    {
        return tempo;
    }

    void PlaybackParameters::setTempo(const uint16_t tempo)
    {
        uint16_t minTempo = rope.config.minSoundTempo.get();
        uint16_t maxTempo = rope.config.maxSoundTempo.get();

        this->tempo = Value::limit(tempo, minTempo, maxTempo);
    }

    uint8_t PlaybackParameters::getVolume() const
    {
        return volume;
    }

    void PlaybackParameters::setVolume(const uint8_t volume)
    {
        uint8_t minVolume = rope.config.minSoundVolume.get();
        uint8_t maxVolume = rope.config.maxSoundVolume.get();

        this->volume = Value::limit(volume, minVolume, maxVolume, Value::Overflow::ChooseHighest);
    }

    uint8_t PlaybackParameters::getRepetitions() const
    {
        return repetitions;
    }

    void PlaybackParameters::setRepetitions(const uint8_t repetitions)
    {
        uint8_t minRepetitions = 1;
        uint8_t maxRepetitions = rope.config.maxSoundRepetitions.get();

        this->repetitions = Value::limit(repetitions, minRepetitions, maxRepetitions);
    }

    int8_t PlaybackParameters::getTransposition() const
    {
        return transposition;
    }

    void PlaybackParameters::setTransposition(const int8_t transposition)
    {
        int8_t minTransposition = rope.config.minSoundTransposition.get();
        int8_t maxTransposition = rope.config.maxSoundTransposition.get();

        this->transposition = Value::limit(transposition, minTransposition, maxTransposition);
    }

    bool PlaybackParameters::mustPlayForever() const
    {
        return playForever;
    }

    void PlaybackParameters::setPlayForever(bool playForever)
    {
        this->playForever = playForever;
    }
}
