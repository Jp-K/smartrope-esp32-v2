#ifndef ROPE_IOT_ROTATION_FINISHED_EVENT
#define ROPE_IOT_ROTATION_FINISHED_EVENT

#include "Rope/IoT/Event.hpp"
#include "Rope/RotationParameters.hpp"

namespace Rope
{
    class RotationFinishedEvent : public Event
    {
    private:
        RotationParameters parameters;
        bool wasInterrupted;

    public:
        RotationFinishedEvent(const std::string& origin, const RotationParameters& parameters, bool wasInterrupted);
        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_ROTATION_FINISHED_EVENT