#ifndef ROPE_IOT_ROPE_MOVE_STARTED_EVENT
#define ROPE_IOT_ROPE_MOVE_STARTED_EVENT

#include "Rope/IoT/Event.hpp"
#include "Rope/MoveParameters.hpp"

namespace Rope
{
    class MoveStartedEvent : public Event
    {
    private:
        MoveParameters parameters;

    public:
        MoveStartedEvent(const std::string& origin, const MoveParameters& parameters);
        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_ROPE_MOVE_STARTED_EVENT