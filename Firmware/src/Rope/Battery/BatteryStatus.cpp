#include "Rope/Battery/BatteryStatus.hpp"

#include <Arduino.h>
#include <math.h>

namespace Rope
{
    BatteryStatus::BatteryStatus(const uint32_t index, const uint16_t analogValue, const float criticalLevel, const float resolutionVoltage) : index(index), analogValue(analogValue), criticalLevel(criticalLevel), resolutionVoltage(resolutionVoltage)
    {

    }

    uint32_t BatteryStatus::getIndex() const
    {
        return index;
    }

    uint16_t BatteryStatus::getAnalogValue() const
    {
        return analogValue;
    }

    float BatteryStatus::getVoltage() const
    {
        return getVoltageMillivolts() / 1000.0f;
    }

    float BatteryStatus::getVoltageMillivolts() const
    {
        float voltage = getADCVoltageMillivolts();

        if (voltage < 2250)
        {
            // ADC voltage < 3000mV
            voltage = (1.2884270620 * voltage) + 112.6195281000;
        }
        else if (voltage >= 2250 && voltage <= 2901)
        {
            // ADC voltage >= 3000mV && <= 3700mV
            voltage = (-0.0003064030 * powf(voltage, 2.0)) + (2.6595058150 * voltage) - 1436.6059690000;
        }
        else if (voltage > 2901)
        {
            // ADC voltage > 3700mV
            voltage = (1.0356739640 * voltage) + 677.7029231000;
        }

        voltage = _max(voltage, 0.0f);
        voltage = _min(voltage, 4200.0f);

        return voltage;
    }

    float BatteryStatus::getADCVoltage() const
    {
        return analogValue * resolutionVoltage;
    }

    float BatteryStatus::getADCVoltageMillivolts() const
    {
        return analogValue * (resolutionVoltage * 1000);
    }

    float BatteryStatus::getLevel() const
    {
        float level = (0.0014285710 * getVoltageMillivolts()) - 4.2857142860;

        level = _max(level, 0.0f);
        level = _min(level, 1.0f);

        return level;
    }

    bool BatteryStatus::isEmpty() const
    {
        return getLevel() <= 0.0f;
    }

    bool BatteryStatus::isFull() const
    {
        return getLevel() >= 1.0f;
    }

    bool BatteryStatus::isCritical() const
    {
        return getLevel() <= criticalLevel;
    }

    float BatteryStatus::getCriticalLevel() const
    {
        return criticalLevel;
    }
} // namespace Rope
