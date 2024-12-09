#include "Rope/IoT/Commands/RotateCommand.hpp"

#include <string>
#include "Rope/RopeToy.hpp"

namespace Rope
{
    RotateCommand::RotateCommand(RopeToy& rope) : Command("ROTATE", rope)
    {
    }

    bool RotateCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        RotationParameters rotationParameters = rope.getDefaultRotationParameters();

        JsonVariant direction = parameters["direction"];
        bool rotateForever = parameters["forever"] | false;
        float duration = parameters["duration"] | 0.0f;
        float degrees = parameters["degrees"] | rotationParameters.getDegrees();
        float speed = parameters["speed"] | rotationParameters.getSpeed();
        bool turnOnLed = parameters["turnOnLed"] | rotationParameters.mustTurnOnLed();
        bool playSound = parameters["playSound"] | rotationParameters.mustPlaySound();

        rotationParameters.setRotateForever(rotateForever);
        rotationParameters.setDuration(duration);
        rotationParameters.setDegrees(degrees);
        rotationParameters.setSpeed(speed);
        rotationParameters.setTurnOnLed(turnOnLed);
        rotationParameters.setPlaySound(playSound);

        if (rotationParameters.mustRotateForever() || rotationParameters.getDuration() > 0.0f || rotationParameters.getDegrees() > 0.0f)
        {
            if (direction == "CLOCKWISE")
            {
                rope.rotateClockwise(requester, rotationParameters);
                return true;
            }

            if (direction == "COUNTERCLOCKWISE")
            {
                rope.rotateCounterClockwise(requester, rotationParameters);
                return true;
            }
        }

        return false;
    }
}