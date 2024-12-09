#ifndef ROPE_KEYPAD_PARAMETERS_HPP
#define ROPE_KEYPAD_PARAMETERS_HPP

#include <stdint.h>

namespace Rope
{
    class RopeToy;
    class KeypadParameters
    {
    private:
        friend class Keypad;
        
        RopeToy& rope;

        uint32_t debounceInterval;
        uint32_t updateInterval;

        KeypadParameters(RopeToy& rope);

    public:

        uint32_t getUpdateInterval() const;
        void setUpdateInterval(uint32_t updateInterval);

        uint32_t getDebounceInterval() const;
        void setDebounceInterval(uint32_t debounceInterval);

    };
}

#endif // ROPE_KEYPAD_PARAMETERS_HPP