#ifndef ROPE_BATTERY_STATUS_HPP
#define ROPE_BATTERY_STATUS_HPP

#include <stdint.h>

namespace Rope
{
  class BatteryStatus
  {

  private:
    uint32_t index;
    uint16_t analogValue;
    float criticalLevel;
    float resolutionVoltage;

  public:
    BatteryStatus(const uint32_t index, const uint16_t analogValue, const float criticalLevel, const float resolutionVoltage);

    uint32_t getIndex() const;
    uint16_t getAnalogValue() const;

    float getVoltage() const;
    float getVoltageMillivolts() const;

    float getADCVoltage() const;
    float getADCVoltageMillivolts() const;

    float getLevel() const;
    float getCriticalLevel() const;
    bool isEmpty() const;
    bool isFull() const;
    bool isCritical() const;
  };

} // namespace Rope

#endif // ROPE_BATTERY_STATUS_HPP