#include "Rope/IoT/Events/MoveFinishedEvent.hpp"

#include "Rope/RopeToy.hpp"

namespace Rope
{
    MoveFinishedEvent::MoveFinishedEvent(const std::string& origin, const MoveParameters& parameters, bool wasInterrupted) :
        Event("MOVE_FINISHED", origin),
        parameters(parameters),
        wasInterrupted(wasInterrupted)
    {

    }

    void MoveFinishedEvent::fillData(const JsonObject& data) const
    {
        data["direction"] = (parameters.getDirection() == MoveParameters::Direction::Forward) ? "FORWARD" : "BACKWARD";
        data["distance"] = parameters.getDistance();
        data["speed"] = parameters.getSpeed();
        data["duration"] = parameters.getDuration();
        data["forever"] = parameters.mustMoveForever();
        data["finishMode"] = wasInterrupted ? "ABORTED" : "NORMAL";
    }
}