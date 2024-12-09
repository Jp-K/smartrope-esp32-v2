#ifndef ROPE_ROTATION_PARAMETERS_HPP
#define ROPE_ROTATION_PARAMETERS_HPP

#include <stdint.h>

namespace Rope
{
    class RopeToy;
    class RotationParameters
    {
    public:
        enum class Direction : uint8_t
        {
            Clockwise,
            CounterClockwise
        };

    private:
        friend class RopeToy;
        RopeToy& rope;

        RotationParameters::Direction direction = RotationParameters::Direction::Clockwise;
        float duration = 0.0f;
        float degrees;
        float speed;

        bool turnOnLed;
        bool playSound;
        bool rotateForever = false;

            RotationParameters(RopeToy& rope);

    public:
        Direction getDirection() const;
        void setDirection(Direction direction);

        float getDuration() const;
        void setDuration(float duration);

        float getDegrees() const;
        void setDegrees(float degrees);

        float getSpeed() const;
        void setSpeed(float speed);

        bool mustTurnOnLed() const;
        void setTurnOnLed(bool turnOnLed);

        bool mustPlaySound() const;
        void setPlaySound(bool playSound);

        bool mustRotateForever() const;
        void setRotateForever(bool rotateForever);
    };
}

#endif // ROPE_ROTATION_PARAMETERS_HPP