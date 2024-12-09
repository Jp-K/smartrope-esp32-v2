#include "Rope/Program/Instructions/RotateClockwiseInstruction.hpp"

#include "Rope/RopeToy.hpp"

namespace Rope
{
    RotateClockwiseInstruction::RotateClockwiseInstruction() : Instruction("ROTATE_CLOCKWISE")
    {

    }

    void RotateClockwiseInstruction::execute(const std::string& requester, RopeToy& rope, AsyncStartCallback startCallback, AsyncFinishCallback finishCallback) const
    {
        rope.rotateClockwise(requester, startCallback, finishCallback);
    }

    void RotateClockwiseInstruction::abort(const std::string& requester, RopeToy& rope) const
    {
        rope.stop(requester);
    }
} // namespace Rope
