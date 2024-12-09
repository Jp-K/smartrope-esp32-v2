#ifndef ROPE_IOT_BATTERY_STATUS_EVENT
#define ROPE_IOT_BATTERY_STATUS_EVENT

#include "Rope/IoT/Event.hpp"
#include "Rope/Battery/BatteryStatus.hpp"

namespace Rope
{
    class BatteryStatusEvent : public Event
    {
    private:
        BatteryStatus batteryStatus;
    public:
        BatteryStatusEvent(const std::string& origin, const BatteryStatus& status);
        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_BATTERY_STATUS_EVENT