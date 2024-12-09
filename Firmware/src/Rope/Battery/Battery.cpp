#include "Rope/Battery/Battery.hpp"

#include <Arduino.h>

#include "Rope/RopeToy.hpp"
#include "Rope/Util/Value.hpp"
#include "Rope/IoT/Events/BatteryStatusEvent.hpp"

namespace Rope
{
    Battery::Battery(RopeToy& rope, uint8_t pin, uint8_t chargerPin, uint32_t maxSamples, float criticalLevel) :
        rope(rope),
        pin(pin),
        criticalLevel(criticalLevel),
        maxSamples(maxSamples),
        analogAverage(maxSamples),
        status(0, 0, 0, 0)
    {
        pinMode(pin, INPUT);
        analogReadResolution(ADC_RESOLUTION_BITS);

        pinMode(chargerPin, OUTPUT);
        digitalWrite(chargerPin, HIGH);

        adcResolutionVoltage = ADC_REFERENCE_VOLTAGE / (powf(2.0f, ADC_RESOLUTION_BITS) - 1);
    }

    void Battery::reportStatus()
    {
        BatteryStatusEvent event(Event::Origin::Rope, status);
        rope.IoT.notifyEvent(&event);
        //logStatus();
    }

    void Battery::updateStatus()
    {
        analogAverage.addSample(analogRead(pin));

        // uint16_t currentValue = analogAverage.getValue();
        // uint16_t previousValue = status.getAnalogValue();

        // status = BatteryStatus(++sampleCount, _min(currentValue, previousValue), criticalLevel, adcResolutionVoltage);

        // Battery right implementation
        // status = BatteryStatus(++sampleCount, analogAverage.getValue(), criticalLevel, adcResolutionVoltage);

        status = simulate();
    }

    void updateTask(void *param)
    {
        Battery *battery = static_cast<Battery *>(param);
        uint32_t updateInterval = battery->rope.config.batteryUpdateInterval.get();

        while (true)
        {
            battery->updateStatus();
            vTaskDelay(updateInterval / portTICK_PERIOD_MS);
        }
    }

    void reportTask(void *param)
    {
        Battery *battery = static_cast<Battery *>(param);
        uint32_t reportInterval = battery->rope.config.batteryReportInterval.get();

        while (true)
        {
            battery->reportStatus();
            vTaskDelay(reportInterval / portTICK_PERIOD_MS);
        }
    }

    void Battery::initialize()
    {
        updateStatus();
        reportStatus();

        uint32_t updateInterval = rope.config.batteryUpdateInterval.get();
        uint32_t reportInterval = rope.config.batteryReportInterval.get();

        
        xTaskCreatePinnedToCore(
            updateTask,                  
            "UpdateBatteryStatusTask",   
            2048,                       
            this,                        
            1,                           
            &updateTaskHandle,          
            1                            
        );

        xTaskCreatePinnedToCore(
            reportTask,                  
            "ReportBatteryStatusTask",   
            2048,                        
            this,                        
            1,                           
            &reportTaskHandle,        
            1                          
        );
    }

    BatteryStatus Battery::simulate()
    {
        static uint32_t beg = millis();
        
        float analog100percent = (2950 / adcResolutionVoltage) / 1000.0f;
        float analog0percent = (2200 / adcResolutionVoltage) / 1000.0f;
        float range = analog100percent - analog0percent;

        float timeToConsume = ((30.0f * 60.0f) + 0.0f) * 1000;
        float analogValue = map(millis() - beg, 0, timeToConsume, analog100percent, analog0percent);

        BatteryStatus status(++sampleCount, analogValue, criticalLevel, adcResolutionVoltage);

        if (status.getLevel() <= 0.0f){
            beg = millis();
        }

        return status;
    }

    uint32_t Battery::getSampleCount() const
    {
        return sampleCount;
    }

    BatteryStatus Battery::getStatus() const
    {
        if (sampleCount == 0)
        {
            return BatteryStatus(0, powf(2.0f, ADC_RESOLUTION_BITS) - 1, criticalLevel, adcResolutionVoltage);
        }

        return status;
    }

    uint32_t Battery::getMaxSamples() const
    {
        return maxSamples;
    }

    float Battery::getCriticalLevel() const
    {
        return criticalLevel;
    }

    float Battery::getADCReferenceVoltage() const
    {
        return ADC_REFERENCE_VOLTAGE;
    }

    float Battery::getADCResolutionBits() const
    {
        return ADC_RESOLUTION_BITS;
    }

    float Battery::getADCResolutionVoltage() const
    {
        return adcResolutionVoltage;
    }

    void Battery::logStatus()
    {
        logInfo();
        logState();
        logGauge();
    }

    void Battery::logGauge()
    {
        const uint16_t gaugeSize = 50;
        const char full = '=';
        const char empty = '-';

        char gaugeBuffer[gaugeSize + 1];
        gaugeBuffer[gaugeSize] = '\0';

        uint16_t filled = gaugeSize * status.getLevel();

        for (uint16_t i = 1; i <= gaugeSize; i++)
        {
            if (i <= filled)
            {
                gaugeBuffer[i - 1] = full;
            }
            else
            {
                gaugeBuffer[i - 1] = empty;
            }
        }

        // h4pUserEvent("[%s]", gaugeBuffer);
    }

    void Battery::logState()
    {
        if (status.isFull())
        {
            //h4pUserEvent("Battery state: FULL", NULL);
        }
        else if (status.isEmpty())
        {
            //h4pUserEvent("Battery state: EMPTY", NULL);
        }
        else if (status.isCritical())
        {
            //h4pUserEvent("Battery state: CRITICAL", NULL);
        }
        else
        {
            //h4pUserEvent("Battery state: DISCHARGING", NULL);
        }
    }

    void Battery::logInfo()
    {
        //h4pUserEvent("Sample: %d", status.getIndex());
        //h4pUserEvent("Real analog value: %d", analogRead(pin));
        //h4pUserEvent("Mean analog value: %d", status.getAnalogValue());
        //h4pUserEvent("ADC voltage (V): %.2f", status.getADCVoltage());
        //h4pUserEvent("ADC voltage (mV): %.2f", status.getADCVoltageMillivolts());
        //h4pUserEvent("Battery voltage (V): %.2f", status.getVoltage());
        //h4pUserEvent("Battery voltage (mV): %.2f", status.getVoltageMillivolts());
        //h4pUserEvent("Battery level: %.0f%%", floorf(status.getLevel() * 100));
    }
} // namespace Rope
