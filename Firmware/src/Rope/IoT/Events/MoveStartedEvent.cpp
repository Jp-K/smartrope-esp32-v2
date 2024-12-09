#include "Rope/IoT/Events/MoveStartedEvent.hpp"

#include "Rope/RopeToy.hpp"

namespace Rope
{
    MoveStartedEvent::MoveStartedEvent(const std::string& origin, const MoveParameters& parameters) :
        Event("MOVE_STARTED", origin),
        parameters(parameters)
    {

    }

    void MoveStartedEvent::fillData(const JsonObject& data) const
    {
        data["direction"] = (parameters.getDirection() == MoveParameters::Direction::Forward) ? "FORWARD" : "BACKWARD";
        data["distance"] = parameters.getDistance();
        data["speed"] = parameters.getSpeed();
        data["duration"] = parameters.getDuration();
        data["forever"] = parameters.mustMoveForever();
    }
}