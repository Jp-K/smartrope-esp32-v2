#ifndef ROPE_PINOUT_H
#define ROPE_PINOUT_H

#include <stdint.h>

namespace Rope
{
    class Pinout
    {
    public:        
        // Pins for the four directional LEDs
        const uint8_t frontLed = 27;
        const uint8_t rightLed = 21;
        const uint8_t backLed = 23;
        const uint8_t leftLed = 22;
        const uint8_t centerLed = 19;

        // Pin used by the buzzer to play sounds
        const uint8_t buzzer = 25;

        // Analog pin used by the keypad to read the buttons pressed
        const uint8_t keypad = 32;

        // Pin used for the keypad interrupt
        const uint8_t keypadInterrupt = 32;

        // Pin used to measure the battery tension/charge
        const uint8_t battery = 33;

        // Pin used to enable and disable the battery charger circuit
        const uint8_t charger = 26;

        // Pins used to drive the left motor (MOTOR_A)
        const uint8_t leftMotorBlue = 2;
        const uint8_t leftMotorPink = 14;
        const uint8_t leftMotorYellow = 18;
        const uint8_t leftMotorOrange = 12;

        // Pins used to drive the right motor (MOTOR_B)
        const uint8_t rightMotorBlue = 4;
        const uint8_t rightMotorPink = 16;
        const uint8_t rightMotorYellow = 5;
        const uint8_t rightMotorOrange = 17;
    };
}

#endif // ROPE_PINOUT_H