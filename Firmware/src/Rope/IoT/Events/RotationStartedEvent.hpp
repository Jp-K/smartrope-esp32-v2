#ifndef ROPE_IOT_ROTATION_STARTED_EVENT
#define ROPE_IOT_ROTATION_STARTED_EVENT

#include "Rope/IoT/Event.hpp"
#include "Rope/RotationParameters.hpp"

namespace Rope
{
    class RotationStartedEvent : public Event
    {
    private:
        RotationParameters parameters;

    public:
        RotationStartedEvent(const std::string& origin, const RotationParameters& parameters);
        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_ROTATION_STARTED_EVENT