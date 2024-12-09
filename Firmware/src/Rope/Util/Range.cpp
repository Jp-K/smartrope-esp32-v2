#include "Rope/Util/Range.hpp"

namespace Rope
{

    Range::Range()
    {

    }

    Range::Range(const uint16_t min, const uint16_t max) : min(min), max(max)
    {
    }

    bool Range::contains(const uint16_t value) const
    {
        return (value >= this->min && value <= this->max);
    }

    uint16_t Range::getMin() const
    {
        return this->min;
    }

    uint16_t Range::getMax() const
    {
        return this->max;
    }

} // namespace Rope
