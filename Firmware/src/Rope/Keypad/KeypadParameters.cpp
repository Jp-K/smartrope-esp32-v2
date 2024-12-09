#include "Rope/Keypad/KeypadParameters.hpp"

#include "Rope/RopeToy.hpp"
#include "Rope/Util/Value.hpp"

namespace Rope
{
    KeypadParameters::KeypadParameters(RopeToy& rope) : rope(rope)
    {

    }

    uint32_t KeypadParameters::getUpdateInterval() const
    {
        return updateInterval;
    }

    void KeypadParameters::setUpdateInterval(uint32_t updateInterval)
    {
        uint32_t minInterval = 5;
        uint32_t maxInterval = 200;

        this->updateInterval = Value::limit(updateInterval, minInterval, maxInterval);
    }

    uint32_t KeypadParameters::getDebounceInterval() const
    {
        return debounceInterval;
    }

    void KeypadParameters::setDebounceInterval(uint32_t debounceInterval)
    {
        uint32_t minInterval = 5;
        uint32_t maxInterval = 200;

        this->debounceInterval = Value::limit(debounceInterval, minInterval, maxInterval);
    }
}