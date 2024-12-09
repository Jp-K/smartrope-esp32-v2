#include "Rope/Util/GPIORegister.hpp"

#include <Arduino.h>

#include "Rope/Util/BinaryString.hpp"

namespace Rope
{
    uint32_t GPIORegister::enable(uint32_t mask)
    {
        REG_WRITE(GPIO_ENABLE_W1TS_REG, mask);

        return (uint32_t)REG_READ(GPIO_ENABLE_REG);
    }

    uint32_t GPIORegister::enable(const std::string& mask)
    {
        BinaryString binaryMask(mask);

        if (binaryMask.isValid())
        {
            return enable(binaryMask.toUnsignedInt());
        }

        return (uint32_t)REG_READ(GPIO_ENABLE_REG);
    }

    uint32_t GPIORegister::update(uint32_t mask, uint32_t value)
    {
        uint32_t pinsToTurnOn = value & mask;
        uint32_t pinsToTurnOff = (~pinsToTurnOn) & mask;
        uint32_t newValue = REG_READ(GPIO_OUT_REG);
        newValue |= pinsToTurnOn;
        newValue &= (~pinsToTurnOff);

        REG_WRITE(GPIO_OUT_REG, newValue);
        return (uint32_t)REG_READ(GPIO_OUT_REG);
    }

    uint32_t GPIORegister::update(uint32_t mask, const std::string& value)
    {
        BinaryString binaryValue(value);

        if (binaryValue.isValid())
        {
            return update(mask, binaryValue.toUnsignedInt());
        }

        return (uint32_t)REG_READ(GPIO_OUT_REG);
    }

    uint32_t GPIORegister::update(const std::string& mask, uint32_t value)
    {
        BinaryString binaryMask(mask);

        if (binaryMask.isValid())
        {
            return update(binaryMask.toUnsignedInt(), value);
        }

        return (uint32_t)REG_READ(GPIO_OUT_REG);
    }

    uint32_t GPIORegister::update(const std::string& mask, const std::string& value)
    {
        BinaryString binaryMask(mask);
        BinaryString binaryValue(value);

        if (binaryMask.isValid() && binaryValue.isValid())
        {
            return update(binaryMask.toUnsignedInt(), binaryValue.toUnsignedInt());
        }

        return (uint32_t)REG_READ(GPIO_OUT_REG);
    }

    uint32_t GPIORegister::read()
    {
        return REG_READ(GPIO_OUT_REG);
    }
}