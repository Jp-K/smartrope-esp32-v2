#include "Rope/Program/Instructions/MoveBackwardInstruction.hpp"

#include "Rope/RopeToy.hpp"

namespace Rope
{
    MoveBackwardInstruction::MoveBackwardInstruction() : Instruction("MOVE_BACKWARD")
    {

    }

    void MoveBackwardInstruction::execute(const std::string& requester, RopeToy& rope, AsyncStartCallback startCallback, AsyncFinishCallback finishCallback) const
    {
        rope.moveBackward(requester, startCallback, finishCallback);
    }

    void MoveBackwardInstruction::abort(const std::string& requester, RopeToy& rope) const
    {
        rope.stop(requester);
    }
} // namespace Rope
