#ifndef ROPE_MOTORS_HPP
#define ROPE_MOTORS_HPP

#include <functional>
#include <stdint.h>
#include <vector>
#include <Arduino.h>


#include "Rope/Common/NamedEntityContainer.hpp"
#include "Rope/Motors/Stepper28BYJ_48.hpp"

using StopCallback = std::function<bool(void)>;
using FinishedCallback = std::function<void(float, uint32_t)>;

namespace Rope
{

  class RopeToy;
  class Motors : public NamedEntityContainer<StepperMotor>
  {
  private:
    RopeToy& rope;

    void configureMotors();

    bool isAlreadyActive();
    bool invalidSteps(uint32_t steps) const;
    bool invalidInterval(float interval) const;
    bool invalidSpeed(float stepsPerSecond) const;

    void synchronizedMove(float stepsPerSecond, StepperMotor::Direction leftMotorDirection, StepperMotor::Direction rightMotorDirection, StopCallback stopCallback, FinishedCallback finishedCallback);
    void turnOff();

  public:
    Stepper28BYJ_48 left;
    Stepper28BYJ_48 right;
    bool active = false;

    uint32_t currentMillisecond;
    uint32_t currentStep;

    TaskHandle_t moveTask = nullptr;

    Motors(RopeToy& rope);

    void synchronizedMoveSteps(uint32_t steps, float stepsPerSecond, StepperMotor::Direction leftMotorDirection, StepperMotor::Direction rightMotorDirection, FinishedCallback finishedCallback = nullptr);
    void synchronizedMoveInterval(float seconds, float stepsPerSecond, StepperMotor::Direction leftMotorDirection, StepperMotor::Direction rightMotorDirection, FinishedCallback finishedCallback = nullptr);
    void synchronizedMoveForever(float stepsPerSecond, StepperMotor::Direction leftMotorDirection, StepperMotor::Direction rightMotorDirection, FinishedCallback finishedCallback = nullptr);

    float stepsToSeconds(float steps, float stepsPerSecond);
    float secondsToSteps(float seconds, float stepsPerSecond);

    void stop();
  };

} // namespace Rope

#endif // ROPE_MOTORS_HPP