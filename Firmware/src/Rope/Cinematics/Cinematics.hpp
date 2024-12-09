#ifndef ROPE_CINEMATICS_HPP
#define ROPE_CINEMATICS_HPP

#include <stdint.h>

namespace Rope
{
    class RopeToy;
    class Cinematics
    {
    private:
        RopeToy& rope;
    public:
        Cinematics(RopeToy& rope);

        float motorStepsToWheelRotation(float motorSteps);
        float wheelRotationToMotorSteps(float wheelRotation);

        float wheelRotationToWheelDisplacement(float wheelRotation);
        float wheelDisplacementToWheelRotation(float wheelDisplacement);

        float wheelDisplacementToMotorSteps(float wheelDisplacement);
        float motorStepsToWheelDisplacement(float motorSteps);

        float wheelDisplacementToBodyRotation(float wheelDisplacement);
        float bodyRotationToWheelDisplacement(float bodyRotation);

        float wheelRotationToBodyRotation(float wheelRotation);
        float bodyRotationToWheelRotation(float bodyRotation);

        float motorStepsToBodyRotation(float motorSteps);
        float bodyRotationToMotorSteps(float bodyRotation);

        float motorStepsToBodyDisplacement(float motorSteps);
        float bodyDisplacementToMotorSteps(float bodyDisplacement);

        float getMinWheelRotationSpeed();
        float getMaxWheelRotationSpeed();

        float getMinWheelDisplacementSpeed();
        float getMaxWheelDisplacementSpeed();
        
        float getMinBodyDisplacementSpeed();
        float getMaxBodyDisplacementSpeed();

        float getMinBodyRotationSpeed();
        float getMaxBodyRotationSpeed();

        float getMinWheelRotation();
        float getMinBodyDisplacement();
        float getMinBodyRotation();
    };
}

#endif // ROPE_CINEMATICS_HPP