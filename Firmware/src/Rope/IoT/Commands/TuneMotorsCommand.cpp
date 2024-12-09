#include "Rope/IoT/Commands/TuneMotorsCommand.hpp"

#include <string>

#include "Rope/RopeToy.hpp"
#include "Rope/Keypad/KeypadParameters.hpp"

namespace Rope
{
    TuneMotorsCommand::TuneMotorsCommand(RopeToy& rope) : Command("TUNE_MOTORS", rope)
    {
    }

    bool TuneMotorsCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        std::string leftSequence = parameters["left"] | rope.config.leftMotorSequence.get();
        std::string rightSequence = parameters["right"] | rope.config.rightMotorSequence.get();

        rope.motors.left.setWireSequence(leftSequence);
        rope.motors.right.setWireSequence(rightSequence);

        return true;
    }
}