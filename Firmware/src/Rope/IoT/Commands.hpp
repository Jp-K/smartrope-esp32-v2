#ifndef ROPE_IOT_COMMANDS_HPP
#define ROPE_IOT_COMMANDS_HPP

#include <vector>


#include "Rope/Common/NamedEntityContainer.hpp"
#include "Rope/IoT/Commands/MoveCommand.hpp"
#include "Rope/IoT/Commands/RotateCommand.hpp"
#include "Rope/IoT/Commands/ToggleLedCommand.hpp"
#include "Rope/IoT/Commands/TuneSoundCommand.hpp"
#include "Rope/IoT/Commands/PlaySoundCommand.hpp"
#include "Rope/IoT/Commands/StopSoundCommand.hpp"
#include "Rope/IoT/Commands/PressButtonCommand.hpp"
#include "Rope/IoT/Commands/TogglePinCommand.hpp"
#include "Rope/IoT/Commands/SetGPIORegisterCommand.hpp"
#include "Rope/IoT/Commands/StopRopeCommand.hpp"
#include "Rope/IoT/Commands/InsertInstructionCommand.hpp"
#include "Rope/IoT/Commands/RemoveInstructionCommand.hpp"
#include "Rope/IoT/Commands/ReplaceInstructionCommand.hpp"
#include "Rope/IoT/Commands/ClearMemoryCommand.hpp"
#include "Rope/IoT/Commands/ResizeMemoryCommand.hpp"
#include "Rope/IoT/Commands/ExecuteProgramCommand.hpp"
#include "Rope/IoT/Commands/TuneKeypadCommand.hpp"
#include "Rope/IoT/Commands/TuneMotorsCommand.hpp"
#include "Rope/IoT/Commands/SendRobotStateCommand.hpp"

namespace Rope
{
    class Commands : public NamedEntityContainer<Command>
    {
    public:
        MoveCommand move;
        RotateCommand rotate;
        ToggleLedCommand toggleLed;
        TuneSoundCommand tuneSound;
        PlaySoundCommand playSound;
        StopSoundCommand stopSound;
        PressButtonCommand pressButton;
        TogglePinCommand togglePin;
        SetGPIORegisterCommand setGPIORegister;
        StopRopeCommand stopRopeCommand;
        InsertInstructionCommand insertInstruction;
        RemoveInstructionCommand removeInstruction;
        ReplaceInstructionCommand replaceInstruction;
        ClearMemoryCommand clearMemory;
        ResizeMemoryCommand resizeMemory;
        ExecuteProgramCommand executeProgram;
        TuneKeypadCommand tuneKeypad;
        TuneMotorsCommand tuneMotors;
        SendRobotStateCommand sendRobotState;

        Commands(RopeToy& rope);
    };
}

#endif // ROPE_IOT_COMMANDS_HPP