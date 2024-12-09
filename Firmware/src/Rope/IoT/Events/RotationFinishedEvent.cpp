#include "Rope/IoT/Events/RotationFinishedEvent.hpp"

#include "Rope/RopeToy.hpp"

namespace Rope
{
    RotationFinishedEvent::RotationFinishedEvent(const std::string& origin, const RotationParameters& parameters, bool wasInterrupted) :
        Event("ROTATION_FINISHED", origin),
        parameters(parameters),
        wasInterrupted(wasInterrupted)
    {

    }

    void RotationFinishedEvent::fillData(const JsonObject& data) const
    {
        data["direction"] = (parameters.getDirection() == RotationParameters::Direction::Clockwise) ? "CLOCKWISE" : "COUNTERCLOCKWISE";
        data["degrees"] = parameters.getDegrees();
        data["speed"] = parameters.getSpeed();
        data["duration"] = parameters.getDuration();
        data["forever"] = parameters.mustRotateForever();
        data["finishMode"] = wasInterrupted ? "ABORTED" : "NORMAL";
    }
}