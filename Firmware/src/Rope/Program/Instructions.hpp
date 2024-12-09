#ifndef ROPE_PROGRAM_INSTRUCTIONS_HPP
#define ROPE_PROGRAM_INSTRUCTIONS_HPP

#include "Rope/Common/NamedEntityContainer.hpp"
#include "Rope/Program/Instructions/MoveForwardInstruction.hpp"
#include "Rope/Program/Instructions/MoveBackwardInstruction.hpp"
#include "Rope/Program/Instructions/RotateClockwiseInstruction.hpp"
#include "Rope/Program/Instructions/RotateCounterClockwiseInstruction.hpp"

namespace Rope
{
    class Instructions : public NamedEntityContainer<Instruction>
    {
    public:
        MoveForwardInstruction moveForward;
        MoveBackwardInstruction moveBackward;
        RotateClockwiseInstruction rotateClockwise;
        RotateCounterClockwiseInstruction rotateCounterClockwise;

        Instructions() : NamedEntityContainer("Instructions")
        {
            addEntity(moveForward);
            addEntity(moveBackward);
            addEntity(rotateClockwise);
            addEntity(rotateCounterClockwise);
        }
    };
}

#endif // ROPE_PROGRAM_INSTRUCTIONS_HPP