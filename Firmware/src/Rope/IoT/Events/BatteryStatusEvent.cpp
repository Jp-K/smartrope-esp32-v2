#include "Rope/IoT/Events/BatteryStatusEvent.hpp"

namespace Rope
{
    BatteryStatusEvent::BatteryStatusEvent(const std::string& origin, const BatteryStatus& status) :
        Event("BATTERY_STATUS", origin),
        batteryStatus(status)
    {

    }

    void BatteryStatusEvent::fillData(const JsonObject& data) const
    {
        std::string state;

        if (batteryStatus.isFull())
        {
            state = "FULL";
        }
        else if (batteryStatus.isEmpty())
        {
            state = "EMPTY";
        }
        else if (batteryStatus.isCritical())
        {
            state = "CRITICAL";
        }
        else
        {
            state = "DISCHARGING";
        }

        data["level"] = batteryStatus.getLevel();
        data["state"] = state;
        data["critical_treshold"] = batteryStatus.getCriticalLevel();

        JsonObject voltage = data.createNestedObject("voltage");

        voltage["volts"] = batteryStatus.getVoltage();
        voltage["millivolts"] = batteryStatus.getVoltageMillivolts();
    }
}