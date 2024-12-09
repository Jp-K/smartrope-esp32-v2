#include "Rope/Motors/Motors.hpp"

#include <cmath>

#include "Rope/RopeToy.hpp"
#include "Rope/Util/Timer.hpp"
#include "Rope/Util/GPIORegister.hpp"
#include "Rope/Util/BinaryString.hpp"

namespace Rope
{
    Motors::Motors(RopeToy& rope) : NamedEntityContainer("Motors"),
        rope(rope),
        left("LEFT", rope.pins.leftMotorBlue, rope.pins.leftMotorPink, rope.pins.leftMotorYellow, rope.pins.leftMotorOrange, rope.config.leftMotorSequence.get()),
        right("RIGHT", rope.pins.rightMotorBlue, rope.pins.rightMotorPink, rope.pins.rightMotorYellow, rope.pins.rightMotorOrange, rope.config.rightMotorSequence.get())
    {
        addEntity(left);
        addEntity(right);

        configureMotors();
        turnOff();
    }

    void Motors::configureMotors()
    {
        left.setOperationMode(StepperMotor::OperationMode::HALF_STEP);
        right.setOperationMode(StepperMotor::OperationMode::HALF_STEP);

        uint32_t motorsMask = left.getPinMask() | right.getPinMask();

        // Set the motors pins to output
        GPIORegister::enable(motorsMask);

        // Set both motors to first step
        GPIORegister::update(motorsMask, left.getStepMask() | right.getStepMask());
    }

    bool Motors::isAlreadyActive()
    {
        if (active)
        {
            return true;
        }

        return false;
    }

    bool Motors::invalidSteps(uint32_t steps) const
    {
        if (steps == 0)
        {
            return true;
        }

        return false;
    }

    bool Motors::invalidInterval(float interval) const
    {
        float oneMillisecond = 0.001;

        if (interval < oneMillisecond)
        {
            return true;
        }

        return false;
    }

    bool Motors::invalidSpeed(float stepsPerSecond) const
    {
        if (stepsPerSecond < left.getMinStepsPerSecond())
        {
            return true;
        }

        if (stepsPerSecond > left.getMaxStepsPerSecond())
        {
            return true;
        }

        return false;
    }

    void Motors::synchronizedMoveSteps(uint32_t steps, float stepsPerSecond, StepperMotor::Direction leftMotorDirection, StepperMotor::Direction rightMotorDirection, FinishedCallback finishedCallback)
    {
        if (isAlreadyActive() || invalidSpeed(stepsPerSecond) || invalidSteps(steps))
        {
            return;
        }

        active = true;

        auto stopCallback = [this, steps]()
        {
            return currentStep == steps;
        };

        synchronizedMove(stepsPerSecond, leftMotorDirection, rightMotorDirection, stopCallback, finishedCallback);
    }

    void Motors::synchronizedMoveInterval(float seconds, float stepsPerSecond, StepperMotor::Direction leftMotorDirection, StepperMotor::Direction rightMotorDirection, FinishedCallback finishedCallback)
    {
        if (isAlreadyActive() || invalidSpeed(stepsPerSecond) || invalidInterval(seconds))
        {
            return;
        }

        active = true;

        uint32_t requiredMilliseconds = std::round(seconds * 1000);

        auto stopCallback = [this, requiredMilliseconds]()
        {
            return currentMillisecond == requiredMilliseconds;
        };

        synchronizedMove(stepsPerSecond, leftMotorDirection, rightMotorDirection, stopCallback, finishedCallback);
    }

    void Motors::synchronizedMoveForever(float stepsPerSecond, StepperMotor::Direction leftMotorDirection, StepperMotor::Direction rightMotorDirection, FinishedCallback finishedCallback)
    {
        if (isAlreadyActive() || invalidSpeed(stepsPerSecond))
        {
            return;
        }

        active = true;

        auto stopCallback = []()
        {
            return false;
        };

        synchronizedMove(stepsPerSecond, leftMotorDirection, rightMotorDirection, stopCallback, finishedCallback);
    }

    struct MoveTaskParams
    {
        Motors* motors;
        StepperMotor::Direction leftMotorDirection;
        StepperMotor::Direction rightMotorDirection;
        uint32_t activationInterval;
        StopCallback stopCallback;
        FinishedCallback finishedCallback;
    };

    void moveTaskFunction(void* param)
    {
        MoveTaskParams* params = static_cast<MoveTaskParams*>(param);
        Motors* motors = params->motors;
        uint32_t activationInterval = params->activationInterval;
        //Serial.println("entrou no move task");
        //static portMUX_TYPE _spinlock = portMUX_INITIALIZER_UNLOCKED;
        while (motors->active)
        {
            //taskENTER_CRITICAL(&_spinlock);
            motors->currentMillisecond++;
            //Serial.println("inicio");
            

            if (motors->currentMillisecond % activationInterval == 0)
            {
                motors->currentStep++;
                //Serial.println("antes step");
                motors->left.step(params->leftMotorDirection);
                motors->right.step(params->rightMotorDirection);
                //Serial.println("dps dos steps");
                //Serial.printf("left: %p, right: %p\n", &(motors->left), &(motors->right));
                //Serial.printf("leftPinMask: %u, rightPinMask: %u\n", motors->left.getPinMask(), motors->right.getPinMask());
                uint32_t motorsMask = motors->left.getPinMask() | motors->right.getPinMask();
                uint32_t stepMask = motors->left.getStepMask() | motors->right.getStepMask();
                //Serial.println("pegou mask");

                GPIORegister::update(motorsMask, stepMask);
                //Serial.println("update");

                if (!motors->active || params->stopCallback())
                {
                    motors->active = false;
                    //taskEXIT_CRITICAL(&_spinlock);
                    break;
                }
                //Serial.println("depois if");
            }
            //taskEXIT_CRITICAL(&_spinlock);
            vTaskDelay(1 / portTICK_PERIOD_MS);
        }
        Serial.println("passou motor");

        if (params->finishedCallback)
        {
            params->finishedCallback(motors->currentMillisecond / 1000.0f, motors->currentStep);
        }
        Serial.println("rodou callback");

        delete params;
        //motors->moveTask = nullptr;
        //xTaskNotifyGive(motors->moveTask);
        //vTaskDelete(NULL);
    }

    void Motors::synchronizedMove(float stepsPerSecond, StepperMotor::Direction leftMotorDirection, StepperMotor::Direction rightMotorDirection, StopCallback stopCallback, FinishedCallback finishedCallback)
    {
        currentMillisecond = 0;
        currentStep = 0;
        active = true;

        uint32_t activationInterval = std::round(1000 / stepsPerSecond);

        MoveTaskParams* params = new MoveTaskParams{this, leftMotorDirection, rightMotorDirection, activationInterval, stopCallback, finishedCallback};

        // xTaskCreatePinnedToCore(
        //     moveTaskFunction,        
        //     "MoveTask",         
        //     4096,                   
        //     params,                
        //     1,                  
        //     &moveTask,            
        //     1                       
        // );
        Serial.println("esperando");
        moveTaskFunction(params);
        Serial.println("terminou de esperar");
    }

    float Motors::stepsToSeconds(float steps, float stepsPerSecond)
    {
        return steps / stepsPerSecond;
    }

    float Motors::secondsToSteps(float seconds, float stepsPerSecond)
    {
        return seconds * stepsPerSecond;
    }

    void Motors::turnOff()
    {
        uint32_t motorsMask = left.getPinMask() | right.getPinMask();
        GPIORegister::update(motorsMask, 0);
    }

    void Motors::stop()
    {
        if (active)
        {
            active = false;

            if (moveTask)
            {
                moveTask = nullptr;
            }
        }
    }
} // namespace Rope