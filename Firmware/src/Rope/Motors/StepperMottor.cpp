#include "Rope/Motors/StepperMotor.hpp"

#include "Rope/Util/BinaryString.hpp"

namespace Rope
{
    StepperMotor::StepperMotor(const std::string& name, const std::vector<uint8_t>& pins, float halfStepAngle) : NamedEntity(name)
    {
        setOperationMode(OperationMode::FULL_STEP);
        setPins(pins);

        this->halfStepAngle = halfStepAngle;
        this->fullStepAngle = halfStepAngle * 2.0f;

        this->halfStepsPerRevolution = 360.0f / halfStepAngle;
        this->fullStepsPerRevolution = 360.0f / fullStepAngle;
    }

    float StepperMotor::getMinStepsPerSecond() const
    {
        return MIN_STEPS_PER_SECOND;
    }

    float StepperMotor::getMaxStepsPerSecond() const
    {
        return MAX_STEPS_PER_SECOND;
    }

    uint32_t StepperMotor::getPinMask() const
    {
        return pinMask;
    }

    uint32_t StepperMotor::getStepMask() const
    {
        return stepMaskTable[currentStep];
    }

    uint16_t StepperMotor::getStepsPerRevolution() const
    {
        switch (operationMode)
        {
        case OperationMode::WAVE_STEP:
        case OperationMode::FULL_STEP:
            return fullStepsPerRevolution;
        case OperationMode::HALF_STEP:
            return halfStepsPerRevolution;
        }
    }

    float StepperMotor::getStepAngle() const
    {
        switch (operationMode)
        {
        case OperationMode::WAVE_STEP:
        case OperationMode::FULL_STEP:
            return fullStepAngle;
        case OperationMode::HALF_STEP:
            return halfStepAngle;
        }
    }

    StepperMotor::OperationMode StepperMotor::getOperationMode() const
    {
        return operationMode;
    }

    void StepperMotor::setOperationMode(OperationMode operationMode)
    {
        this->operationMode = operationMode;
        reset();
    }

    void StepperMotor::reset()
    {
        switch (operationMode)
        {
        case OperationMode::WAVE_STEP:
            currentStep = 0;
            stepIncrement = 2;
            return;
        case OperationMode::FULL_STEP:
            currentStep = 1;
            stepIncrement = 2;
            return;
        case OperationMode::HALF_STEP:
            currentStep = 0;
            stepIncrement = 1;
            return;
        }
    }

    void StepperMotor::step(Direction direction)
    {
        uint8_t tableSize = stepMaskTable.size();
        int8_t increment = stepIncrement * static_cast<int8_t>(direction);

        // h4pUserEvent("Step before: %d", currentStep);
        currentStep = (tableSize + currentStep + increment) % tableSize;
        // h4pUserEvent("Step after: %d", currentStep);
    }

    void StepperMotor::setPins(const std::vector<uint8_t>& pins)
    {
        this->pins = pins;
        createPinMask();
        createStepMaskTable();
        reset();

        //for (auto pin : pins)
        //{
        //    h4pUserEvent("Motor %s pin: %d", getName().c_str(), pin);
        //}

        BinaryString binaryMask(pinMask);
        //h4pUserEvent("Pin mask:  %s (%d)", binaryMask.toString().c_str(), binaryMask.toUnsignedInt());

        for (auto stepMask : stepMaskTable)
        {
            BinaryString binaryStep(stepMask);
            //h4pUserEvent("Step mask: %s (%d)", binaryStep.toString().c_str(), binaryStep.toUnsignedInt());
        }
    }

    void StepperMotor::createPinMask()
    {
        pinMask = 0;

        for (auto pin : pins)
        {
            pinMask |= (1 << pin);
        }
    }

    void StepperMotor::createStepMaskTable()
    {
        uint8_t pinCount = pins.size();

        stepMaskTable.clear();

        for (uint8_t i = 0; i < pinCount; i++)
        {
            uint32_t fullStepMask = (1 << pins[i]);
            uint32_t halfStepMask = fullStepMask | (1 << pins[(i + 1) % pinCount]);

            stepMaskTable.push_back(fullStepMask);
            stepMaskTable.push_back(halfStepMask);
        }
    }

    float StepperMotor::stepsToRevolutions(float steps) const
    {
        return steps / getStepsPerRevolution();
    }

    float StepperMotor::revolutionsToSteps(float revolutions) const
    {
        return revolutions * getStepsPerRevolution();
    }

    float StepperMotor::stepsToRotation(float steps) const
    {
        return steps * getStepAngle();
    }

    float StepperMotor::rotationToSteps(float degrees) const
    {
        return degrees / getStepAngle();
    }
}