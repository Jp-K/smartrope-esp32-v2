#include "Rope/Cinematics/Cinematics.hpp"

#include <math.h>

#include "Rope/RopeToy.hpp"

namespace Rope
{
    Cinematics::Cinematics(RopeToy& rope) : rope(rope)
    {

    }

    // Wheel rotation to motor steps

    float Cinematics::motorStepsToWheelRotation(float motorSteps)
    {
        return rope.motors.left.stepsToRotation(motorSteps);
    }

    float Cinematics::wheelRotationToMotorSteps(float wheelRotation)
    {
        return rope.motors.left.rotationToSteps(wheelRotation);
    }

    // Wheel rotation to wheel displacement

    float Cinematics::wheelRotationToWheelDisplacement(float wheelRotation)
    {
        return (wheelRotation * PI * rope.config.wheelsDiameter.get()) / 360.0f;
    }

    float Cinematics::wheelDisplacementToWheelRotation(float wheelDisplacement)
    {
        return (wheelDisplacement * 360.0f) / (PI * rope.config.wheelsDiameter.get());
    }

    // Wheel displacement to motor steps

    float Cinematics::wheelDisplacementToMotorSteps(float wheelDisplacement)
    {
        float wheelRotation = wheelDisplacementToWheelRotation(wheelDisplacement);
        return wheelRotationToMotorSteps(wheelRotation);
    }

    float Cinematics::motorStepsToWheelDisplacement(float motorSteps)
    {
        float wheelRotation = motorStepsToWheelRotation(motorSteps);
        return wheelRotationToWheelDisplacement(wheelRotation);
    }

    // Wheel displacement to body rotation

    float Cinematics::wheelDisplacementToBodyRotation(float wheelDisplacement)
    {
        return (wheelDisplacement * 360.0) / (PI * rope.config.distanceBetweenWheels.get());
    }

    float Cinematics::bodyRotationToWheelDisplacement(float bodyRotation)
    {
        return (bodyRotation * PI * rope.config.distanceBetweenWheels.get()) / 360.0f;
    }

    // Wheel rotation to body rotation

    float Cinematics::wheelRotationToBodyRotation(float wheelRotation)
    {
        float wheelDisplacement = wheelRotationToWheelDisplacement(wheelRotation);
        return wheelDisplacementToBodyRotation(wheelDisplacement);
    }

    float Cinematics::bodyRotationToWheelRotation(float bodyRotation)
    {
        float wheelDisplacement = bodyRotationToWheelDisplacement(bodyRotation);
        return wheelDisplacementToWheelRotation(wheelDisplacement);
    }

    //  Motor steps to body rotation

    float Cinematics::motorStepsToBodyRotation(float motorSteps)
    {
        float wheelRotation = motorStepsToWheelRotation(motorSteps);
        return wheelRotationToBodyRotation(wheelRotation);
    }

    float Cinematics::bodyRotationToMotorSteps(float bodyRotation)
    {
        float wheelRotation = bodyRotationToWheelRotation(bodyRotation);
        return wheelRotationToMotorSteps(wheelRotation);
    }

    // Motor steps to body displacement

    float Cinematics::motorStepsToBodyDisplacement(float motorSteps)
    {
        float wheelDisplacement = motorStepsToWheelDisplacement(motorSteps);
        return wheelDisplacement;
    }

    float Cinematics::bodyDisplacementToMotorSteps(float bodyDisplacement)
    {
        float wheelDisplacement = bodyDisplacement;
        return wheelDisplacementToMotorSteps(wheelDisplacement);
    }

    // Wheel displacement speed

    float Cinematics::getMinWheelDisplacementSpeed()
    {
        float minMotorSteps = rope.motors.left.getMinStepsPerSecond();
        return motorStepsToWheelDisplacement(minMotorSteps);
    }

    float Cinematics::getMaxWheelDisplacementSpeed()
    {
        float maxMotorSteps = rope.motors.left.getMaxStepsPerSecond();
        return motorStepsToWheelDisplacement(maxMotorSteps);
    }

    // Wheel rotation speed

    float Cinematics::getMinWheelRotationSpeed()
    {
        float minMotorSteps = rope.motors.left.getMinStepsPerSecond();
        return motorStepsToWheelRotation(minMotorSteps);
    }

    float Cinematics::getMaxWheelRotationSpeed()
    {
        float maxMotorSteps = rope.motors.left.getMaxStepsPerSecond();
        return motorStepsToWheelRotation(maxMotorSteps);
    }

    // Body displacement speed

    float Cinematics::getMinBodyDisplacementSpeed()
    {
        float minMotorSteps = rope.motors.left.getMinStepsPerSecond();
        return motorStepsToBodyDisplacement(minMotorSteps);
    }

    float Cinematics::getMaxBodyDisplacementSpeed()
    {
        float maxMotorSteps = rope.motors.left.getMaxStepsPerSecond();
        return motorStepsToBodyDisplacement(maxMotorSteps);
    }

    // Body rotation speed

    float Cinematics::getMinBodyRotationSpeed()
    {
        float minMotorSteps = rope.motors.left.getMinStepsPerSecond();
        return motorStepsToBodyRotation(minMotorSteps);
    }

    float Cinematics::getMaxBodyRotationSpeed()
    {
        float maxMotorSteps = rope.motors.left.getMaxStepsPerSecond();
        return motorStepsToBodyRotation(maxMotorSteps);
    }

    // Wheel rotation limit
    float Cinematics::getMinWheelRotation()
    {
        return motorStepsToWheelRotation(1);
    }

    // Body displacement limit
    float Cinematics::getMinBodyDisplacement()
    {
        return motorStepsToBodyDisplacement(1);
    }

    // Body rotation limit
    float Cinematics::getMinBodyRotation()
    {
        return motorStepsToBodyRotation(1);
    }
}