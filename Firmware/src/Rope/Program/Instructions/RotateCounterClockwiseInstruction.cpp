#include "Rope/Program/Instructions/RotateCounterClockwiseInstruction.hpp"

#include "Rope/RopeToy.hpp"

namespace Rope
{
    RotateCounterClockwiseInstruction::RotateCounterClockwiseInstruction() : Instruction("ROTATE_COUNTERCLOCKWISE")
    {

    }

    void RotateCounterClockwiseInstruction::execute(const std::string& requester, RopeToy& rope, AsyncStartCallback startCallback, AsyncFinishCallback finishCallback) const
    {
        rope.rotateCounterClockwise(requester, startCallback, finishCallback);
    }

    void RotateCounterClockwiseInstruction::abort(const std::string& requester, RopeToy& rope) const
    {
        rope.stop(requester);
    }
} // namespace Rope
