#ifndef ROPE_MOVE_BACKWARD_INSTRUCTION_HPP
#define ROPE_MOVE_BACKWARD_INSTRUCTION_HPP

#include "Rope/Program/Instruction.hpp"

namespace Rope
{
    class MoveBackwardInstruction : public Instruction
    {
    private:
        friend class Instructions;
        MoveBackwardInstruction();
    public:

        void execute(const std::string& requester, RopeToy& rope, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr) const;
        void abort(const std::string& requester, RopeToy& rope) const;
    };
} // namespace Rope

#endif // ROPE_MOVE_BACKWARD_INSTRUCTION_HPP