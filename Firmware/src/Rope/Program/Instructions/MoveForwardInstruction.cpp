#include "Rope/Program/Instructions/MoveForwardInstruction.hpp"

#include "Rope/RopeToy.hpp"

namespace Rope
{
    MoveForwardInstruction::MoveForwardInstruction() : Instruction("MOVE_FORWARD")
    {

    }

    void MoveForwardInstruction::execute(const std::string& requester, RopeToy& rope, AsyncStartCallback startCallback, AsyncFinishCallback finishCallback) const
    {
        rope.moveForward(requester, startCallback, finishCallback);
    }

    void MoveForwardInstruction::abort(const std::string& requester, RopeToy& rope) const
    {
        rope.stop(requester);
    }
} // namespace Rope
