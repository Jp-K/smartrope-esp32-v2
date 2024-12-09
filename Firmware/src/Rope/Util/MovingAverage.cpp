#include "Rope/Util/MovingAverage.hpp"

#include <Arduino.h>

namespace Rope
{
    MovingAverage::MovingAverage(const uint16_t maxSamples) :
        maxSamples(maxSamples),
        samples(maxSamples)
    {
        clear();
    }

    void MovingAverage::clear()
    {
        for (uint16_t i = 0; i < samples.size(); i++)
        {
            samples[i] = 0;
        }

        index = 0;
        readSamples = 0;
    }

    void MovingAverage::addSample(const uint16_t sample)
    {
        samples[index] = sample;
        index = (index + 1) % samples.size();

        readSamples = _min(readSamples + 1, samples.capacity());
    }

    uint16_t MovingAverage::getValue() const
    {
        if (isEmpty())
        {
            return 0;
        }

        uint32_t value = 0;

        for (uint16_t i = 0; i < samples.size(); i++)
        {
            value = value + samples[i];
        }

        return value / readSamples;
    }

    uint16_t MovingAverage::getReadSamples() const
    {
        return readSamples;
    }

    uint16_t MovingAverage::getMaxSamples() const
    {
        return maxSamples;
    }

    bool MovingAverage::isFilled() const
    {
        return readSamples == samples.capacity();
    }

    bool MovingAverage::isEmpty() const
    {
        return readSamples == 0;
    }
} // namespace Rope
