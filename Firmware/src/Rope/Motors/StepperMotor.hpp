#ifndef ROPE_STEPPER_MOTOR_HPP
#define ROPE_STEPPER_MOTOR_HPP

#include <stdint.h>
#include <vector>
#include <string>

#include "Rope/Common/NamedEntity.hpp"

// This class is a base class for driving stepper mottors using the ESP32
// GPIO register
//
// It assumes that all the pins of the motor are in rgeister GPIO_OUT_REG, 
// that is, that all the pins are in the GPIO 0 to 31. Pins 32 to 39 will 
// not work
//
// It also assumes that the pins are passed to the class in the right sequence
// that they should be activated. For example, if pins 7, 5, 8, 1 are passed,
// they will be actived in the following sequence:
// 
// Stage 0: 7
// Stage 1: 7, 5
// Stage 2: 5
// Stage 3: 5, 8
// Stage 4: 8
// Stage 5: 8, 1
// Stage 6: 1
// Stage 7: 1, 7

namespace Rope
{
    class StepperMotor : public NamedEntity
    {
    public:
        enum class Direction : int8_t
        {
            Clockwise = 1,
            CounterClockwise = -1
        };

        enum class OperationMode : uint8_t
        {
            WAVE_STEP,
            FULL_STEP,
            HALF_STEP
        };

    private:
        static constexpr float MIN_STEPS_PER_SECOND = 1.0f;
        static constexpr float MAX_STEPS_PER_SECOND = 1000.0f;

        float halfStepAngle;
        float fullStepAngle;

        uint16_t halfStepsPerRevolution;
        uint16_t fullStepsPerRevolution;

        std::vector<uint8_t> pins;
        OperationMode operationMode;

        uint32_t pinMask;
        std::vector<uint32_t> stepMaskTable;

        uint8_t currentStep;
        uint8_t stepIncrement;

        void createPinMask();
        void createStepMaskTable();

    protected:
        virtual void setPins(const std::vector<uint8_t>& pins) final;
        
    public:
        StepperMotor(const std::string& name, const std::vector<uint8_t>& pins, float halfStepAngle);

        virtual void setOperationMode(OperationMode operationMode) final;
        virtual OperationMode getOperationMode() const final;

        virtual void reset() final;
        virtual void step(Direction direction) final;

        virtual uint32_t getPinMask() const final;
        virtual uint32_t getStepMask() const final;
        
        virtual uint16_t getStepsPerRevolution() const final;
        virtual float getStepAngle() const final;
        
        virtual float getMinStepsPerSecond() const final;
        virtual float getMaxStepsPerSecond() const final;
        
        virtual float stepsToRevolutions(float steps) const final;
        virtual float revolutionsToSteps(float revolutions) const final;

        virtual float stepsToRotation(float steps) const final;
        virtual float rotationToSteps(float degrees) const final;
    };
}

#endif // ROPE_STEPPER_MOTOR_HPP