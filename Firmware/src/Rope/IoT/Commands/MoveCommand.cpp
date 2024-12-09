#include "Rope/IoT/Commands/MoveCommand.hpp"

#include <string>

#include "Rope/RopeToy.hpp"

namespace Rope
{
    MoveCommand::MoveCommand(RopeToy& rope) : Command("MOVE", rope)
    {
    }

    bool MoveCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        MoveParameters moveParameters = rope.getDefaultMoveParameters();

        JsonVariant direction = parameters["direction"];
        bool moveForever = parameters["forever"] | false;
        float duration = parameters["duration"] | 0.0f;
        float distance = parameters["distance"] | moveParameters.getDistance();
        float speed = parameters["speed"] | moveParameters.getSpeed();
        bool turnOnLed = parameters["turnOnLed"] | moveParameters.mustTurnOnLed();
        bool playSound = parameters["playSound"] | moveParameters.mustPlaySound();

        moveParameters.setMoveForever(moveForever);
        moveParameters.setDuration(duration);
        moveParameters.setDistance(distance);
        moveParameters.setSpeed(speed);
        moveParameters.setTurnOnLed(turnOnLed);
        moveParameters.setPlaySound(playSound);

        if (moveParameters.mustMoveForever() || moveParameters.getDuration() > 0.0f || moveParameters.getDistance() > 0.0f)
        {
            if (direction == "FORWARD")
            {
                rope.moveForward(requester, moveParameters);
                return true;
            }

            if (direction == "BACKWARD")
            {
                rope.moveBackward(requester, moveParameters);
                return true;
            }
        }

        return false;
    }
}