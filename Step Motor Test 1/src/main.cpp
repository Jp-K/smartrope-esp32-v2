#include <Arduino.h>

/*
========================================================
Motor A:
    Pino 1 Driver (Blue)    --> 16 do Arduino
    Pino 2 Driver (Pink)    --> 15 do Arduino
    Pino 3 Driver (Yellow)  --> 14 do Arduino
    Pino 4 Driver (Orange)  --> 13 do Arduino

Motor B:
    Pino 5 Driver (Blue)    -->  9 do Arduino
    Pino 6 Driver (Pink)    --> 10 do Arduino
    Pino 7 Driver (Yellow)  --> 11 do Arduino
    Pino 8 Driver (Orange)  --> 12 do Arduino
*/

// THIS CODE IS THE CORRECT

#define MOTOR_A_BLUE 13
#define MOTOR_A_PINK 14
#define MOTOR_A_YELLOW 15
#define MOTOR_A_ORANGE 16

#define MOTOR_B_BLUE 9
#define MOTOR_B_PINK 10
#define MOTOR_B_YELLOW 11
#define MOTOR_B_ORANGE 12

// #define MOTOR_A_BLUE 16
// #define MOTOR_A_PINK 15
// #define MOTOR_A_YELLOW 14
// #define MOTOR_A_ORANGE 13

// #define MOTOR_B_BLUE 9
// #define MOTOR_B_PINK 10
// #define MOTOR_B_YELLOW 11
// #define MOTOR_B_ORANGE 12

// MICROSTEP_DELAY TESTED: 1000, 750, 500, 250, 100, 50, 25
// MINIMUM MICROSTEP_DELAY = 25

#define MICROSTEP_DELAY 25 // In microseconds

#define REVOLUTION_STEPS 512 // PORQUE SIM

#define CLOCKWISE 0
#define COUNTERCLOCKWISE 1

#define FORWARD 0
#define BACKWARD 1
#define LEFT 0
#define RIGHT 1

void turnOffMotorA()
{
    digitalWrite(MOTOR_A_BLUE, LOW);
    digitalWrite(MOTOR_A_PINK, LOW);
    digitalWrite(MOTOR_A_YELLOW, LOW);
    digitalWrite(MOTOR_A_ORANGE, LOW);
}

void turnOffMotorB()
{
    digitalWrite(MOTOR_B_BLUE, LOW);
    digitalWrite(MOTOR_B_PINK, LOW);
    digitalWrite(MOTOR_B_YELLOW, LOW);
    digitalWrite(MOTOR_B_ORANGE, LOW);
}

void microStepMotorA(uint8_t stepIndex)
{
    switch (stepIndex)
    {
    case 0:
        digitalWrite(MOTOR_A_BLUE, LOW);
        digitalWrite(MOTOR_A_PINK, LOW);
        digitalWrite(MOTOR_A_YELLOW, LOW);
        digitalWrite(MOTOR_A_ORANGE, HIGH);
        break;
    case 1:
        digitalWrite(MOTOR_A_BLUE, LOW);
        digitalWrite(MOTOR_A_PINK, LOW);
        digitalWrite(MOTOR_A_YELLOW, HIGH);
        digitalWrite(MOTOR_A_ORANGE, HIGH);
        break;
    case 2:
        digitalWrite(MOTOR_A_BLUE, LOW);
        digitalWrite(MOTOR_A_PINK, LOW);
        digitalWrite(MOTOR_A_YELLOW, HIGH);
        digitalWrite(MOTOR_A_ORANGE, LOW);
        break;
    case 3:
        digitalWrite(MOTOR_A_BLUE, LOW);
        digitalWrite(MOTOR_A_PINK, HIGH);
        digitalWrite(MOTOR_A_YELLOW, HIGH);
        digitalWrite(MOTOR_A_ORANGE, LOW);
        break;
    case 4:
        digitalWrite(MOTOR_A_BLUE, LOW);
        digitalWrite(MOTOR_A_PINK, HIGH);
        digitalWrite(MOTOR_A_YELLOW, LOW);
        digitalWrite(MOTOR_A_ORANGE, LOW);
        break;
    case 5:
        digitalWrite(MOTOR_A_BLUE, HIGH);
        digitalWrite(MOTOR_A_PINK, HIGH);
        digitalWrite(MOTOR_A_YELLOW, LOW);
        digitalWrite(MOTOR_A_ORANGE, LOW);
        break;
    case 6:
        digitalWrite(MOTOR_A_BLUE, HIGH);
        digitalWrite(MOTOR_A_PINK, LOW);
        digitalWrite(MOTOR_A_YELLOW, LOW);
        digitalWrite(MOTOR_A_ORANGE, LOW);
        break;
    case 7:
        digitalWrite(MOTOR_A_BLUE, HIGH);
        digitalWrite(MOTOR_A_PINK, LOW);
        digitalWrite(MOTOR_A_YELLOW, LOW);
        digitalWrite(MOTOR_A_ORANGE, HIGH);
        break;
    }

    delayMicroseconds(MICROSTEP_DELAY);
}

void revolutionMotorA(uint8_t direction)
{
    if (direction == CLOCKWISE)
    {
        for (int steps = 1; steps <= REVOLUTION_STEPS; steps++)
        {
            for (int stepIndex = 0; stepIndex < 8; stepIndex++)
            {
                microStepMotorA(stepIndex);
            }
        }
    }
    else if (direction == COUNTERCLOCKWISE)
    {
        for (int steps = 1; steps <= REVOLUTION_STEPS; steps++)
        {
            for (int i = 7; i >= 0; i--)
            {
                microStepMotorA(i);
            }
        }
    }
}

void microStepMotorB(uint8_t stepIndex)
{
    switch (stepIndex)
    {
    case 0:
        digitalWrite(MOTOR_B_BLUE, LOW);
        digitalWrite(MOTOR_B_PINK, LOW);
        digitalWrite(MOTOR_B_YELLOW, LOW);
        digitalWrite(MOTOR_B_ORANGE, HIGH);
        break;
    case 1:
        digitalWrite(MOTOR_B_BLUE, LOW);
        digitalWrite(MOTOR_B_PINK, LOW);
        digitalWrite(MOTOR_B_YELLOW, HIGH);
        digitalWrite(MOTOR_B_ORANGE, HIGH);
        break;
    case 2:
        digitalWrite(MOTOR_B_BLUE, LOW);
        digitalWrite(MOTOR_B_PINK, LOW);
        digitalWrite(MOTOR_B_YELLOW, HIGH);
        digitalWrite(MOTOR_B_ORANGE, LOW);
        break;
    case 3:
        digitalWrite(MOTOR_B_BLUE, LOW);
        digitalWrite(MOTOR_B_PINK, HIGH);
        digitalWrite(MOTOR_B_YELLOW, HIGH);
        digitalWrite(MOTOR_B_ORANGE, LOW);
        break;
    case 4:
        digitalWrite(MOTOR_B_BLUE, LOW);
        digitalWrite(MOTOR_B_PINK, HIGH);
        digitalWrite(MOTOR_B_YELLOW, LOW);
        digitalWrite(MOTOR_B_ORANGE, LOW);
        break;
    case 5:
        digitalWrite(MOTOR_B_BLUE, HIGH);
        digitalWrite(MOTOR_B_PINK, HIGH);
        digitalWrite(MOTOR_B_YELLOW, LOW);
        digitalWrite(MOTOR_B_ORANGE, LOW);
        break;
    case 6:
        digitalWrite(MOTOR_B_BLUE, HIGH);
        digitalWrite(MOTOR_B_PINK, LOW);
        digitalWrite(MOTOR_B_YELLOW, LOW);
        digitalWrite(MOTOR_B_ORANGE, LOW);
        break;
    case 7:
        digitalWrite(MOTOR_B_BLUE, HIGH);
        digitalWrite(MOTOR_B_PINK, LOW);
        digitalWrite(MOTOR_B_YELLOW, LOW);
        digitalWrite(MOTOR_B_ORANGE, HIGH);
        break;
    }

    delayMicroseconds(MICROSTEP_DELAY);
}

void revolutionMotorB(uint8_t direction)
{
    if (direction == CLOCKWISE)
    {
        for (int steps = 1; steps <= REVOLUTION_STEPS; steps++)
        {
            for (int stepIndex = 0; stepIndex < 8; stepIndex++)
            {
                microStepMotorB(stepIndex);
            }
        }
    }
    else if (direction == COUNTERCLOCKWISE)
    {
        for (int steps = 1; steps <= REVOLUTION_STEPS; steps++)
        {
            for (int stepIndex = 7; stepIndex >= 0; stepIndex--)
            {
                microStepMotorB(stepIndex);
            }
        }
    }
}


void parallelMicroStepLeftRight(uint8_t stepIndex)
{
    switch (stepIndex)
    {
    case 0:

        digitalWrite(MOTOR_A_BLUE, LOW);
        digitalWrite(MOTOR_B_BLUE, LOW);

        digitalWrite(MOTOR_A_PINK, LOW);
        digitalWrite(MOTOR_B_PINK, LOW);

        digitalWrite(MOTOR_A_YELLOW, LOW);
        digitalWrite(MOTOR_B_YELLOW, LOW);

        digitalWrite(MOTOR_A_ORANGE, HIGH);
        digitalWrite(MOTOR_B_ORANGE, HIGH);

        break;
    case 1:
        digitalWrite(MOTOR_A_BLUE, LOW);
        digitalWrite(MOTOR_B_BLUE, LOW);

        digitalWrite(MOTOR_A_PINK, LOW);
        digitalWrite(MOTOR_B_PINK, LOW);

        digitalWrite(MOTOR_A_YELLOW, HIGH);
        digitalWrite(MOTOR_B_YELLOW, HIGH);

        digitalWrite(MOTOR_A_ORANGE, HIGH);
        digitalWrite(MOTOR_B_ORANGE, HIGH);

        break;
    case 2:
        digitalWrite(MOTOR_A_BLUE, LOW);
        digitalWrite(MOTOR_B_BLUE, LOW);

        digitalWrite(MOTOR_A_PINK, LOW);
        digitalWrite(MOTOR_B_PINK, LOW);

        digitalWrite(MOTOR_A_YELLOW, HIGH);
        digitalWrite(MOTOR_B_YELLOW, HIGH);

        digitalWrite(MOTOR_A_ORANGE, LOW);
        digitalWrite(MOTOR_B_ORANGE, LOW);

        break;
    case 3:
        digitalWrite(MOTOR_A_BLUE, LOW);
        digitalWrite(MOTOR_B_BLUE, LOW);

        digitalWrite(MOTOR_A_PINK, HIGH);
        digitalWrite(MOTOR_B_PINK, HIGH);

        digitalWrite(MOTOR_A_YELLOW, HIGH);
        digitalWrite(MOTOR_B_YELLOW, HIGH);

        digitalWrite(MOTOR_A_ORANGE, LOW);
        digitalWrite(MOTOR_B_ORANGE, LOW);
        break;
    case 4:
        digitalWrite(MOTOR_A_BLUE, LOW);
        digitalWrite(MOTOR_B_BLUE, LOW);

        digitalWrite(MOTOR_A_PINK, HIGH);
        digitalWrite(MOTOR_B_PINK, HIGH);

        digitalWrite(MOTOR_A_YELLOW, LOW);
        digitalWrite(MOTOR_B_YELLOW, LOW);

        digitalWrite(MOTOR_A_ORANGE, LOW);
        digitalWrite(MOTOR_B_ORANGE, LOW);
        break;
    case 5:
        digitalWrite(MOTOR_A_BLUE, HIGH);
        digitalWrite(MOTOR_B_BLUE, HIGH);

        digitalWrite(MOTOR_A_PINK, HIGH);
        digitalWrite(MOTOR_B_PINK, HIGH);

        digitalWrite(MOTOR_A_YELLOW, LOW);
        digitalWrite(MOTOR_B_YELLOW, LOW);

        digitalWrite(MOTOR_A_ORANGE, LOW);
        digitalWrite(MOTOR_B_ORANGE, LOW);
        break;
    case 6:
        digitalWrite(MOTOR_A_BLUE, HIGH);
        digitalWrite(MOTOR_B_BLUE, HIGH);

        digitalWrite(MOTOR_A_PINK, LOW);
        digitalWrite(MOTOR_B_PINK, LOW);

        digitalWrite(MOTOR_A_YELLOW, LOW);
        digitalWrite(MOTOR_B_YELLOW, LOW);

        digitalWrite(MOTOR_A_ORANGE, LOW);
        digitalWrite(MOTOR_B_ORANGE, LOW);
        break;
    case 7:
        digitalWrite(MOTOR_A_BLUE, HIGH);
        digitalWrite(MOTOR_B_BLUE, HIGH);

        digitalWrite(MOTOR_A_PINK, LOW);
        digitalWrite(MOTOR_B_PINK, LOW);

        digitalWrite(MOTOR_A_YELLOW, LOW);
        digitalWrite(MOTOR_B_YELLOW, LOW);

        digitalWrite(MOTOR_A_ORANGE, HIGH);
        digitalWrite(MOTOR_B_ORANGE, HIGH);
        break;
    }

    delayMicroseconds(MICROSTEP_DELAY);
}

void parallelRevolutionLeftRight(uint8_t direction)
{
    if (direction == LEFT)
    {
        for (int steps = 1; steps <= REVOLUTION_STEPS; steps++)
        {
            for (int stepIndex = 0; stepIndex < 8; stepIndex++)
            {
                parallelMicroStepLeftRight(stepIndex);
            }
        }
    }
    else if (direction == RIGHT)
    {
        for (int steps = 1; steps <= REVOLUTION_STEPS; steps++)
        {
            for (int stepIndex = 7; stepIndex >= 0; stepIndex--)
            {
                parallelMicroStepLeftRight(stepIndex);
            }
        }
    }
}


void parallelMicroStepForwardBackward(uint8_t stepIndex)
{
    switch (stepIndex)
    {
    case 0:
        digitalWrite(MOTOR_A_BLUE, LOW);
	    digitalWrite(MOTOR_B_BLUE, HIGH);	

        digitalWrite(MOTOR_A_PINK, LOW);
        digitalWrite(MOTOR_B_PINK, LOW);

        digitalWrite(MOTOR_A_YELLOW, LOW);
        digitalWrite(MOTOR_B_YELLOW, LOW);

        digitalWrite(MOTOR_A_ORANGE, HIGH);
        digitalWrite(MOTOR_B_ORANGE, HIGH);
        break;
    case 1:
        digitalWrite(MOTOR_A_BLUE, LOW);
        digitalWrite(MOTOR_B_BLUE, HIGH);

        digitalWrite(MOTOR_A_PINK, LOW);
        digitalWrite(MOTOR_B_PINK, LOW);

        digitalWrite(MOTOR_A_YELLOW, HIGH);
        digitalWrite(MOTOR_B_YELLOW, LOW);

        digitalWrite(MOTOR_A_ORANGE, HIGH);
        digitalWrite(MOTOR_B_ORANGE, LOW);
        break;
    case 2:
        digitalWrite(MOTOR_A_BLUE, LOW);
        digitalWrite(MOTOR_B_BLUE, HIGH);

        digitalWrite(MOTOR_A_PINK, LOW);
        digitalWrite(MOTOR_B_PINK, HIGH);

        digitalWrite(MOTOR_A_YELLOW, HIGH);
        digitalWrite(MOTOR_B_YELLOW, LOW);

        digitalWrite(MOTOR_A_ORANGE, LOW);
        digitalWrite(MOTOR_B_ORANGE, LOW);

        break;
    case 3:
        digitalWrite(MOTOR_A_BLUE, LOW);
        digitalWrite(MOTOR_B_BLUE, LOW);


        digitalWrite(MOTOR_A_PINK, HIGH);
        digitalWrite(MOTOR_B_PINK, HIGH);

        digitalWrite(MOTOR_A_YELLOW, HIGH);
        digitalWrite(MOTOR_B_YELLOW, LOW);

        digitalWrite(MOTOR_A_ORANGE, LOW);
        digitalWrite(MOTOR_B_ORANGE, LOW);
        break;
    case 4:
        digitalWrite(MOTOR_A_BLUE, LOW);
        digitalWrite(MOTOR_B_BLUE, LOW);

        digitalWrite(MOTOR_A_PINK, HIGH);
        digitalWrite(MOTOR_B_PINK, HIGH);

        digitalWrite(MOTOR_A_YELLOW, LOW);
        digitalWrite(MOTOR_B_YELLOW, HIGH);

        digitalWrite(MOTOR_A_ORANGE, LOW);
        digitalWrite(MOTOR_B_ORANGE, LOW);
        break;
    case 5:
        digitalWrite(MOTOR_A_BLUE, HIGH);
        digitalWrite(MOTOR_B_BLUE, LOW);

        digitalWrite(MOTOR_A_PINK, HIGH);
        digitalWrite(MOTOR_B_PINK, LOW);

        digitalWrite(MOTOR_A_YELLOW, LOW);
        digitalWrite(MOTOR_B_YELLOW, HIGH);

        digitalWrite(MOTOR_A_ORANGE, LOW);
        digitalWrite(MOTOR_B_ORANGE, LOW);

        break;
    case 6:
        digitalWrite(MOTOR_A_BLUE, HIGH);
        digitalWrite(MOTOR_B_BLUE, LOW);

        digitalWrite(MOTOR_A_PINK, LOW);
        digitalWrite(MOTOR_B_PINK, LOW);

        digitalWrite(MOTOR_A_YELLOW, LOW);
        digitalWrite(MOTOR_B_YELLOW, HIGH);

        digitalWrite(MOTOR_A_ORANGE, LOW);
        digitalWrite(MOTOR_B_ORANGE, HIGH);
        break;
    case 7:
        digitalWrite(MOTOR_A_BLUE, HIGH);
        digitalWrite(MOTOR_B_BLUE, LOW);

        digitalWrite(MOTOR_A_PINK, LOW);
        digitalWrite(MOTOR_B_PINK, LOW);

        digitalWrite(MOTOR_A_YELLOW, LOW);
        digitalWrite(MOTOR_B_YELLOW, LOW);

        digitalWrite(MOTOR_A_ORANGE, HIGH);
        digitalWrite(MOTOR_B_ORANGE, HIGH);

        break;
    }

    delayMicroseconds(MICROSTEP_DELAY);
}



void parallelRevolutionForwardBackward(uint8_t direction)
{
    if (direction == BACKWARD)
    {
        for (int steps = 1; steps <= REVOLUTION_STEPS; steps++)
        {
            for (int stepIndex = 0; stepIndex < 8; stepIndex++)
            {
                parallelMicroStepForwardBackward(stepIndex);
            }
        }
    }
    else if (direction == FORWARD)
    {
        for (int steps = 1; steps <= REVOLUTION_STEPS; steps++)
        {
            for (int stepIndex = 7; stepIndex >= 0; stepIndex--)
            {
                parallelMicroStepForwardBackward(stepIndex);
            }
        }
    }
}

void setup()
{
    pinMode(MOTOR_A_BLUE, OUTPUT);
    pinMode(MOTOR_A_PINK, OUTPUT);
    pinMode(MOTOR_A_YELLOW, OUTPUT);
    pinMode(MOTOR_A_ORANGE, OUTPUT);

    pinMode(MOTOR_B_BLUE, OUTPUT);
    pinMode(MOTOR_B_PINK, OUTPUT);
    pinMode(MOTOR_B_YELLOW, OUTPUT);
    pinMode(MOTOR_B_ORANGE, OUTPUT);

    Serial.begin(9600);

    delay(10000);
}

void loop()
{
    Serial.println("Forward");

    parallelRevolutionForwardBackward(FORWARD);

    turnOffMotorA();
    turnOffMotorB();

    delay(500);


    Serial.println("Backward");

    parallelRevolutionForwardBackward(BACKWARD);

    turnOffMotorA();
    turnOffMotorB();

    delay(500);

    Serial.println("Left");

    parallelRevolutionLeftRight(LEFT);

    turnOffMotorA();
    turnOffMotorB();

    delay(500);

    Serial.println("Right");

    parallelRevolutionLeftRight(RIGHT);

    turnOffMotorA();
    turnOffMotorB();

    delay(500);
}
