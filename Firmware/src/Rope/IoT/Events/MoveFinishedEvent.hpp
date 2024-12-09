#ifndef ROPE_IOT_MOVE_FINISHED_EVENT
#define ROPE_IOT_MOVE_FINISHED_EVENT

#include "Rope/IoT/Event.hpp"
#include "Rope/MoveParameters.hpp"

namespace Rope
{
    class MoveFinishedEvent : public Event
    {
    private:
        MoveParameters parameters;
        bool wasInterrupted;

    public:
        MoveFinishedEvent(const std::string& origin, const MoveParameters& parameters, bool wasInterrupted);
        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_MOVE_FINISHED_EVENT