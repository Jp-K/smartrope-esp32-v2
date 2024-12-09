#ifndef ROPE_PLAYBACK_PARAMETERS_HPP
#define ROPE_PLAYBACK_PARAMETERS_HPP

#include <stdint.h>

namespace Rope
{
    class RopeToy;
    class PlaybackParameters
    {
    private:
        friend class Sound;

        RopeToy& rope;

        bool playForever;
        uint16_t tempo;
        uint8_t volume;
        uint8_t repetitions;
        int8_t transposition;

        PlaybackParameters(RopeToy& rope);

    public:
        uint16_t getTempo() const;
        void setTempo(const uint16_t tempo);

        uint8_t getVolume() const;
        void setVolume(const uint8_t volume);

        uint8_t getRepetitions() const;
        void setRepetitions(const uint8_t repetitions);

        int8_t getTransposition() const;
        void setTransposition(const int8_t transposition);

        bool mustPlayForever() const;
        void setPlayForever(bool playForever);
    };
}

#endif // ROPE_PLAYBACK_PARAMETERS_HPP