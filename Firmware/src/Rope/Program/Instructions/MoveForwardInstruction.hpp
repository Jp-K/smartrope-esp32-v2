#ifndef ROPE_MOVE_FORWARD_INSTRUCTION_HPP
#define ROPE_MOVE_FORWARD_INSTRUCTION_HPP

#include "Rope/Program/Instruction.hpp"

namespace Rope
{
    class MoveForwardInstruction : public Instruction
    {
    private:
        friend class Instructions;
        MoveForwardInstruction();
    public:

        void execute(const std::string& requester, RopeToy& rope, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr) const;
        void abort(const std::string& requester, RopeToy& rope) const;
    };
} // namespace Rope

#endif // ROPE_MOVE_FORWARD_INSTRUCTION_HPP