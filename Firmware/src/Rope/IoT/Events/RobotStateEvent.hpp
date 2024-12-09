#ifndef ROPE_IOT_ROBOT_STATE_EVENT
#define ROPE_IOT_ROBOT_STATE_EVENT

#include "Rope/IoT/Event.hpp"

namespace Rope
{
    class RopeToy;
    class RobotStateEvent : public Event
    {
    private:
        RopeToy& rope;
    public:
        RobotStateEvent(const std::string& origin, RopeToy& rope);
        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_ROBOT_STATE_EVENT