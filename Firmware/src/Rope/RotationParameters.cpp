#include "Rope/RotationParameters.hpp"

#include "Rope/RopeToy.hpp"
#include "Rope/Util/Value.hpp"

namespace Rope
{
    RotationParameters::RotationParameters(RopeToy& rope) : rope(rope)
    {

    }

    RotationParameters::Direction RotationParameters::getDirection() const
    {
        return direction;
    }

    void RotationParameters::setDirection(RotationParameters::Direction direction)
    {
        this->direction = direction;
    }

    float RotationParameters::getDuration() const
    {
        return duration;
    }

    void RotationParameters::setDuration(float duration)
    {
        this->duration = duration;
    }

    float RotationParameters::getDegrees() const
    {
        return degrees;
    }

    void RotationParameters::setDegrees(float degrees)
    {
        float minDegrees = rope.cinematics.getMinBodyRotation();

        this->degrees = Value::highest(minDegrees, degrees);
    }

    float RotationParameters::getSpeed() const
    {
        return speed;
    }

    void RotationParameters::setSpeed(float speed)
    {
        float minSpeed = rope.cinematics.getMinBodyRotationSpeed();
        float maxSpeed = rope.cinematics.getMaxBodyRotationSpeed();

        this->speed = Value::limit(speed, minSpeed, maxSpeed, Value::Overflow::ChooseHighest);
    }

    bool RotationParameters::mustTurnOnLed() const
    {
        return turnOnLed;
    }

    void RotationParameters::setTurnOnLed(bool turnOnLed)
    {
        this->turnOnLed = turnOnLed;
    }

    bool RotationParameters::mustPlaySound() const
    {
        return playSound;
    }

    void RotationParameters::setPlaySound(bool playSound)
    {
        this->playSound = playSound;
    }

    bool RotationParameters::mustRotateForever() const
    {
        return rotateForever;
    }

    void RotationParameters::setRotateForever(bool rotateForever)
    {
        this->rotateForever = rotateForever;
    }
}