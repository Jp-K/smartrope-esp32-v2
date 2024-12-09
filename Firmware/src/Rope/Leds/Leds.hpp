#ifndef ROPE_LEDS_HPP
#define ROPE_LEDS_HPP

#include <vector>

#include "Rope/Leds/Led.hpp"
#include "Rope/Common/NamedEntityContainer.hpp"

namespace Rope
{
    class Leds : public NamedEntityContainer<Led>
    {

    public:
        Led front;
        Led right;
        Led back;
        Led left;
        Led center;

        Leds(RopeToy& rope);

        void cycle(uint32_t intervalOn) const;
    };
}

#endif // ROPE_LEDS_HPP