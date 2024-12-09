#include "Rope/MoveParameters.hpp"

#include "Rope/RopeToy.hpp"
#include "Rope/Util/Value.hpp"

namespace Rope
{
    MoveParameters::MoveParameters(RopeToy& rope) : rope(rope)
    {

    }

    MoveParameters::Direction MoveParameters::getDirection() const
    {
        return direction;
    }

    void MoveParameters::setDirection(MoveParameters::Direction direction)
    {
        this->direction = direction;
    }

    float MoveParameters::getDuration() const
    {
        return duration;
    }

    void MoveParameters::setDuration(float duration)
    {
        this->duration = duration;
    }

    float MoveParameters::getDistance() const
    {
        return distance;
    }

    void MoveParameters::setDistance(float distance)
    {
        float minDistance = rope.cinematics.getMinBodyDisplacement();

        this->distance = Value::highest(minDistance, distance);
    }

    float MoveParameters::getSpeed() const
    {
        return speed;
    }

    void MoveParameters::setSpeed(float speed)
    {
        float minSpeed = rope.cinematics.getMinBodyDisplacementSpeed();
        float maxSpeed = rope.cinematics.getMaxBodyDisplacementSpeed();

        this->speed = Value::limit(speed, minSpeed, maxSpeed, Value::Overflow::ChooseHighest);
    }

    bool MoveParameters::mustTurnOnLed() const
    {
        return turnOnLed;
    }

    void MoveParameters::setTurnOnLed(bool turnOnLed)
    {
        this->turnOnLed = turnOnLed;
    }

    bool MoveParameters::mustPlaySound() const
    {
        return playSound;
    }

    void MoveParameters::setPlaySound(bool playSound)
    {
        this->playSound = playSound;
    }

    bool MoveParameters::mustMoveForever() const
    {
        return moveForever;
    }

    void MoveParameters::setMoveForever(bool moveForever)
    {
        this->moveForever = moveForever;
    }
}