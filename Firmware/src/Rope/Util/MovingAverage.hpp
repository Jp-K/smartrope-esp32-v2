#ifndef ROPE_UTIL_MOVING_AVERAGE_HPP
#define ROPE_UTIL_MOVING_AVERAGE_HPP

#include <stdint.h>
#include <vector>

namespace Rope
{
    class MovingAverage
    {
    private:
        std::vector<uint16_t> samples;

        uint16_t maxSamples;
        uint16_t readSamples = 0;
        
        uint16_t index = 0;
    public:
        MovingAverage(const uint16_t maxSamples);

        void addSample(const uint16_t sample);
        void clear();

        uint16_t getReadSamples() const;
        uint16_t getMaxSamples() const;
        uint16_t getValue() const;

        bool isFilled() const;
        bool isEmpty() const;
    };

} // namespace Rope

#endif // ROPE_UTIL_MOVING_AVERAGE_HPP