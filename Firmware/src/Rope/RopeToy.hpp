#ifndef ROPE_TOY_HPP
#define ROPE_TOY_HPP

#include <stdint.h>

#include "Rope/Pinout.h"
#include "Rope/Config/Config.hpp"
#include "Rope/IoT/IoTController.hpp"
#include "Rope/Leds/Leds.hpp"
#include "Rope/Sound/Sound.hpp"
#include "Rope/Battery/Battery.hpp"
#include "Rope/Keypad/Keypad.hpp"
#include "Rope/Motors/Motors.hpp"
#include "Rope/Cinematics/Cinematics.hpp"
#include "Rope/MoveParameters.hpp"
#include "Rope/RotationParameters.hpp"
#include "Rope/Program/Program.hpp"
#include "Rope/Async/Async.hpp"

namespace Rope
{
    class RopeToy
    {
    private:

        bool moving = false;
        bool rotating = false;

        std::string stopRequester;

        void moveStarted(const std::string& requester, MoveParameters parameters, AsyncStartCallback startCallback = nullptr);
        void moveFinished(const std::string& requester, MoveParameters parameters, AsyncFinishCallback finishCallback = nullptr);
        void toggleMoveLed(const std::string& requester, MoveParameters parameters, uint8_t state);
        void playMoveMelody(const std::string& requester, MoveParameters parameters);

        void rotationStarted(const std::string& requester, RotationParameters parameters, AsyncStartCallback startCallback = nullptr);
        void rotationFinished(const std::string& requester, RotationParameters parameters, AsyncFinishCallback finishCallback = nullptr);
        void toggleRotationLed(const std::string& requester, RotationParameters parameters, uint8_t state);
        void playRotationMelody(const std::string& requester, RotationParameters parameters);

        bool cantMoveOrRotate() const;

    public:
        Pinout pins;
        Config config;
        IoTController IoT;

        Leds leds;
        Sound sound;
        Battery battery;
        Keypad keypad;
        Motors motors;
        Cinematics cinematics;
        Program program;

        RopeToy();

        void initialize();

        void moveForward(const std::string& requester, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr);
        void moveForward(const std::string& requester, MoveParameters parameters, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr);
        void moveBackward(const std::string& requester, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr);
        void moveBackward(const std::string& requester, MoveParameters parameters, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr);
        void move(const std::string& requester, MoveParameters parameters, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr);

        void rotateClockwise(const std::string& requester, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr);
        void rotateClockwise(const std::string& requester, RotationParameters parameters, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr);
        void rotateCounterClockwise(const std::string& requester, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr);
        void rotateCounterClockwise(const std::string& requester, RotationParameters parameters, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr);
        void rotate(const std::string& requester, RotationParameters parameters, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr);

        void playErrorFeedback();

        MoveParameters getDefaultMoveParameters();
        RotationParameters getDefaultRotationParameters();

        void stop(const std::string& requester);
    };
}

#endif // ROPE_TOY_HPP