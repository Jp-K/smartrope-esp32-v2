#include "Rope/IoT/Events/RotationStartedEvent.hpp"

#include "Rope/RopeToy.hpp"

namespace Rope
{
    RotationStartedEvent::RotationStartedEvent(const std::string& origin, const RotationParameters& parameters) :
        Event("ROTATION_STARTED", origin),
        parameters(parameters)
    {

    }

    void RotationStartedEvent::fillData(const JsonObject& data) const
    {
        data["direction"] = (parameters.getDirection() == RotationParameters::Direction::Clockwise) ? "CLOCKWISE" : "COUNTERCLOCKWISE";
        data["degrees"] = parameters.getDegrees();
        data["speed"] = parameters.getSpeed();
        data["duration"] = parameters.getDuration();
        data["forever"] = parameters.mustRotateForever();
    }
}