#ifndef ROPE_STEPPER_28BYJ48_HPP
#define ROPE_STEPPER_28BYJ48_HPP

#include "Rope/Motors/StepperMotor.hpp"

#include <stdint.h>

namespace Rope
{
    class Stepper28BYJ_48 : public StepperMotor
    {
    private:

        // See file://./docs/motor-28BYJ-48-gear-ratio.png
        //
        // The gear ratio can be computed with the formula:
        // gearRatio = (32.0/9.0) * (22.0/11.0) * (26.0/9.0) * (31.0/10.0)
        //
        // In the image, the gear ratio was rounded to 63.65, but here the
        // entire value will be used for better precision

        static constexpr float gearReduction = 63.683950617;

        // See file://./docs/motor-28BYJ-48-specs.pdf
        //
        // According to the datasheet, for each half step the inner rotor shaft
        // rotates 5.625 degrees (stride angle). To compute the rotation angle 
        // of the outer motor shaft it's necessary to divide it by the gear ratio

        static constexpr float halfStepAngle = 5.625f / gearReduction;

        uint8_t blueWire;
        uint8_t pinkWire;
        uint8_t yellowWire;
        uint8_t orangeWire;

        std::string wireSequence;
    public:
        Stepper28BYJ_48(const std::string& name, uint8_t blueWire, uint8_t pinkWire, uint8_t yellowWire, uint8_t orangeWire, const std::string& wireSequence);

        void setWireSequence(const std::string& wireSequence);
        const std::string& getWireSequence() const;
    };
}

#endif // ROPE_STEPPER_28BYJ48_HPP