#ifndef ROPE_LED_HPP
#define ROPE_LED_HPP

#include <string>
#include <stdint.h>

#include "Rope/Common/NamedEntity.hpp"

namespace Rope
{
    class RopeToy;
    class Led : public NamedEntity
    {
    private:
        RopeToy& rope;

        bool on;
        uint8_t pin;

        void notifyToggle(const std::string& requester);
    public:
        Led(RopeToy& rope, const std::string& name, uint8_t pin);

        void turnOn(const std::string& requester);
        void turnOff(const std::string& requester);
        void toggle(const std::string& requester);
        void setState(const std::string& requester, uint8_t state);

        void blinkOnce(const std::string& requester, uint32_t intervalOn);

        bool isOn() const;
        bool isOff() const;
    };
} // namespace Rope

#endif // ROPE_LED_HPP