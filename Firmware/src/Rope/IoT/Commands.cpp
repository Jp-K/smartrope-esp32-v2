#include "Rope/IoT/Commands.hpp"

namespace Rope
{
    Commands::Commands(RopeToy& rope) : NamedEntityContainer("Commands"),
        move(rope),
        rotate(rope),
        toggleLed(rope),
        tuneSound(rope),
        playSound(rope),
        stopSound(rope),
        pressButton(rope),
        togglePin(rope),
        setGPIORegister(rope),
        stopRopeCommand(rope),
        insertInstruction(rope),
        removeInstruction(rope),
        replaceInstruction(rope),
        clearMemory(rope),
        resizeMemory(rope),
        executeProgram(rope),
        tuneKeypad(rope),
        tuneMotors(rope),
        sendRobotState(rope)
    {
        addEntity(move);
        addEntity(rotate);
        addEntity(toggleLed);
        addEntity(tuneSound);
        addEntity(playSound);
        addEntity(stopSound);
        addEntity(pressButton);
        addEntity(togglePin);
        addEntity(setGPIORegister);
        addEntity(stopRopeCommand);
        addEntity(insertInstruction);
        addEntity(removeInstruction);
        addEntity(replaceInstruction);
        addEntity(clearMemory);
        addEntity(resizeMemory);
        addEntity(executeProgram);
        addEntity(tuneKeypad);
        addEntity(tuneMotors);
        addEntity(sendRobotState);
    }
}