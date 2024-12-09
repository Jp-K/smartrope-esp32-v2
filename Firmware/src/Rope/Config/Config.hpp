#ifndef ROPE_CONFIG_HPP
#define ROPE_CONFIG_HPP

#include <UnitParams.h>
#include <Arduino.h>

#include "Rope/Config/StringConfig.hpp"
#include "Rope/Config/IntConfig.hpp"
#include "Rope/Config/FloatConfig.hpp"
#include "Rope/Config/BoolConfig.hpp"


namespace Rope
{
    class Config
    {
    public:
        BoolConfig soundEnabled;

        IntConfig minSoundVolume;
        IntConfig maxSoundVolume;
        IntConfig soundVolume;

        IntConfig minSoundTransposition;
        IntConfig maxSoundTransposition;
        IntConfig soundTransposition;

        IntConfig minSoundTempo;
        IntConfig maxSoundTempo;
        IntConfig soundTempo;

        IntConfig maxSoundRepetitions;

        FloatConfig moveDistance;
        FloatConfig moveSpeed;
        FloatConfig rotationSpeed;

        FloatConfig distanceBetweenWheels;
        FloatConfig wheelsDiameter;

        IntConfig minProgramSize;
        IntConfig maxProgramSize;
        IntConfig programSize;

        BoolConfig programCanExecuteForever;
        IntConfig maxProgramRepetitions;

        IntConfig minProgramInstructionDelay;
        IntConfig maxProgramInstructionDelay;
        IntConfig programInstructionDelay;

        IntConfig batterySamples;
        FloatConfig batteryCriticalLevel;
        IntConfig batteryReportInterval;
        IntConfig batteryUpdateInterval;

        IntConfig keypadDebounceInterval;
        IntConfig keypadUpdateInterval;
        IntConfig keypadRepeatInterval;
        IntConfig keypadRepeatDelay;
        BoolConfig keypadEnabled;

        StringConfig leftMotorSequence;
        IntConfig leftMotorCorrection;

        StringConfig rightMotorSequence;
        IntConfig rightMotorCorrection;

        StringConfig moveForwardMelody;
        StringConfig moveBackwardMelody;
        StringConfig rotateClockwiseMelody;
        StringConfig rotateCounterClockwiseMelody;
        StringConfig programFinishedMelody;
        StringConfig programAbortedMelody;
        StringConfig actionErrorMelody;

        StringConfig frontButtonMelody;
        StringConfig rightButtonMelody;
        StringConfig backButtonMelody;
        StringConfig leftButtonMelody;
        StringConfig centerButtonMelody;

        StringConfig unitName;
        StringConfig unitDescription;
        StringConfig unitSerialNumber;
        StringConfig ownerName;
        StringConfig ownerPhone;
        StringConfig ownerEmail;
        StringConfig ownerAddress;

        void initialize() const;

        Config() :
            soundEnabled("rope_sound_enabled.txt", true),

            minSoundVolume("rope_sound_volume_min.txt", 0),
            maxSoundVolume("rope_sound_volume_max.txt", 8),
            soundVolume("rope_sound_volume.txt", 8),

            minSoundTransposition("rope_sound_transposition_min.txt", -60),
            maxSoundTransposition("rope_sound_transposition_max.txt", 60),
            soundTransposition("rope_sound_transposition.txt", 0),

            minSoundTempo("rope_sound_tempo_min.txt", 1),
            maxSoundTempo("rope_sound_tempo_max.txt", 600),
            soundTempo("rope_sound_tempo.txt", 120),

            maxSoundRepetitions("rope_sound_repetitions_max.txt", 10),

            moveDistance("rope_move_distance.txt", 120.00f),
            moveSpeed("rope_move_speed.txt", 1000000.0f),
            rotationSpeed("rope_rotation_speed.txt", 1000000.0f),

            distanceBetweenWheels("rope_wheels_distance.txt", 69.00f),
            wheelsDiameter("rope_wheels_diameter.txt", 70.10f),

            minProgramSize("rope_program_size_min.txt", 2),
            maxProgramSize("rope_program_size_max.txt", 100),
            programSize("rope_program_size.txt", 45),

            programCanExecuteForever("rope_program_canExecuteForever.txt", true),

            minProgramInstructionDelay("rope_program_instruction_delay_min.txt", 5),
            maxProgramInstructionDelay("rope_program_instruction_delay_max.txt", 2000),
            programInstructionDelay("rope_program_instruction_delay.txt", 150),

            maxProgramRepetitions("rope_program_repetitions_max.txt", 10),

            batterySamples("rope_battery_samples.txt", 20),
            batteryCriticalLevel("rope_battery_level_critical.txt", 0.10f),
            batteryUpdateInterval("rope_battery_update_interval.txt", 50),
            batteryReportInterval("rope_battery_report_interval.txt", 60000),

            keypadEnabled("rope_keypad_enabled.txt", true),
            keypadUpdateInterval("rope_keypad_update_interval.txt", 5),
            keypadDebounceInterval("rope_keypad_debounce_interval.txt", 50),
            keypadRepeatInterval("rope_keypad_repeat_interval.txt", 250),
            keypadRepeatDelay("rope_keypad_repeat_delay.txt", 1250),

            leftMotorSequence("rope_motors_left_sequence.txt", "BPYO"),
            leftMotorCorrection("rope_motors_left_correction.txt", 0),

            rightMotorSequence("rope_motors_right_sequence.txt", "OYPB"),
            rightMotorCorrection("rope_motors_right_correction.txt", 0),

            moveForwardMelody("rope_move_forward_melody.txt", "C#7s |DN7s |EN7q "),
            moveBackwardMelody("rope_move_backward_melody.txt", "EN7s |DN7s |C#7q "),
            rotateClockwiseMelody("rope_rotate_clockwise_melody.txt", "AN6s |A#6s |CN7q "),
            rotateCounterClockwiseMelody("rope_rotate_counter_melody.txt", "CN7s |A#6s |AN6q "),
            programFinishedMelody("rope_program_finished_melody.txt", "BN6D |C#7D |D#7D |EN7S |EN6D "),
            programAbortedMelody("rope_program_aborted_melody.txt", "EN7D |DN7D |CN7D |A#6S "),
            actionErrorMelody("rope_action_error_melody.txt", "EN7D |DN7D |CN7D |A#6S "),
            frontButtonMelody("rope_buttons_front_melody.txt", "C#7D "),
            rightButtonMelody("rope_buttons_right_melody.txt", "BN6D "),
            backButtonMelody("rope_buttons_back_melody.txt", "EN7D "),
            leftButtonMelody("rope_buttons_left_melody.txt", "CN7D "),
            centerButtonMelody("rope_buttons_center_melody.txt", "DN7D "),

            unitName("rope_unit_name.txt", UNIT_NAME),
            unitDescription("rope_unit_description.txt", UNIT_DESCRIPTION),
            unitSerialNumber("rope_unit_serialNumber.txt", UNIT_SERIAL_NUMBER),
            ownerName("rope_owner_name.txt", UNIT_OWNER_NAME),
            ownerPhone("rope_owner_phone.txt", UNIT_OWNER_PHONE),
            ownerEmail("rope_owner_email.txt", UNIT_OWNER_EMAIL),
            ownerAddress("rope_owner_address.txt", UNIT_OWNER_ADDRESS)
        {
            //h4pUserEvent("Config: initialized", NULL);
            Serial.println("entrou config configs");
        }
    };
}

#endif // ROPE_CONFIG_HPP