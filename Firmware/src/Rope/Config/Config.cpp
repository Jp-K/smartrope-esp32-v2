#include "Rope/Config/Config.hpp"

namespace Rope
{

    void Config::initialize() const
    {
        return; // revisar, pois com isso aqui a esp esta dando brown out
        soundEnabled.init();
        minSoundVolume.init();

        maxSoundVolume.init();
        soundVolume.init();

        minSoundTransposition.init();
        maxSoundTransposition.init();
        soundTransposition.init();

        minSoundTempo.init();
        maxSoundTempo.init();
        soundTempo.init();

        maxSoundRepetitions.init();

        moveDistance.init();
        moveSpeed.init();
        rotationSpeed.init();

        distanceBetweenWheels.init();
        wheelsDiameter.init();

        minProgramSize.init();
        maxProgramSize.init();
        programSize.init();

        programCanExecuteForever.init();
        maxProgramRepetitions.init();

        minProgramInstructionDelay.init();
        maxProgramInstructionDelay.init();
        programInstructionDelay.init();

        batterySamples.init();
        batteryCriticalLevel.init();
        batteryReportInterval.init();
        batteryUpdateInterval.init();

        keypadDebounceInterval.init();
        keypadUpdateInterval.init();
        keypadRepeatInterval.init();
        keypadRepeatDelay.init();
        keypadEnabled.init();

        leftMotorSequence.init();
        leftMotorCorrection.init();

        rightMotorSequence.init();
        rightMotorCorrection.init();

        moveForwardMelody.init();
        moveBackwardMelody.init();
        rotateClockwiseMelody.init();
        rotateCounterClockwiseMelody.init();
        programFinishedMelody.init();
        programAbortedMelody.init();
        actionErrorMelody.init();

        frontButtonMelody.init();
        rightButtonMelody.init();
        backButtonMelody.init();
        leftButtonMelody.init();
        centerButtonMelody.init();

        unitName.init();
        unitDescription.init();
        unitSerialNumber.init();
        ownerName.init();
        ownerPhone.init();
        ownerEmail.init();
        ownerAddress.init();
    }

}