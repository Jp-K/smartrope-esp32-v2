#ifndef ROPE_MOVE_PARAMETERS
#define ROPE_MOVE_PARAMETERS

#include <stdint.h>

namespace Rope
{
    class RopeToy;
    class MoveParameters
    {
    public:
        enum class Direction : uint8_t
        {
            Forward,
            Backward
        };

    private:
        friend class RopeToy;

        RopeToy& rope;

        MoveParameters::Direction direction = MoveParameters::Direction::Forward;
        float duration = 0.0f;
        float distance;
        float speed;

        bool turnOnLed;
        bool playSound;
        bool moveForever = false;

        MoveParameters(RopeToy& rope);

    public:
        Direction getDirection() const;
        void setDirection(Direction direction);

        float getDuration() const;
        void setDuration(float duration);

        float getDistance() const;
        void setDistance(float distance);

        float getSpeed() const;
        void setSpeed(float speed);

        bool mustTurnOnLed() const;
        void setTurnOnLed(bool turnOnLed);

        bool mustPlaySound() const;
        void setPlaySound(bool playSound);

        bool mustMoveForever() const;
        void setMoveForever(bool moveForever);
    };
}

#endif // ROPE_MOVE_PARAMETERS