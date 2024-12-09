#ifndef ROPE_BATTERY_HPP
#define ROPE_BATTERY_HPP

#include <stdint.h>

#include "Rope/Battery/BatteryStatus.hpp"
#include "Rope/Util/MovingAverage.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

namespace Rope
{
  class RopeToy;
  class Battery
  {
  private:
    static constexpr float ADC_REFERENCE_VOLTAGE = 3.3f;
    static constexpr uint8_t ADC_RESOLUTION_BITS = 12;

    TaskHandle_t updateTaskHandle = nullptr;
    TaskHandle_t reportTaskHandle = nullptr;

    uint8_t pin;

    uint32_t maxSamples;
    uint32_t sampleCount = 0;

    float adcResolutionVoltage;
    float criticalLevel;

    MovingAverage analogAverage;
    BatteryStatus status;

    BatteryStatus simulate();

    void logStatus();
    void logGauge();
    void logState();
    void logInfo();
  public:

    RopeToy& rope;

    void updateStatus();
    void reportStatus();

    Battery(RopeToy& rope, uint8_t pin, uint8_t chargerPin, uint32_t maxSamples, float criticalLevel);

    void initialize();

    uint32_t getSampleCount() const;
    uint32_t getMaxSamples() const;
    float getADCReferenceVoltage() const;
    float getADCResolutionBits() const;
    float getADCResolutionVoltage() const;

    float getCriticalLevel() const;
    BatteryStatus getStatus() const;
  };

} // namespace Rope

#endif // ROPE_BATTERY_HPP