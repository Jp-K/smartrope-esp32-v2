#ifndef ROPE_ROTATE_CLOCKWISE_INSTRUCTION_HPP
#define ROPE_ROTATE_CLOCKWISE_INSTRUCTION_HPP

#include "Rope/Program/Instruction.hpp"

namespace Rope
{
    class RotateClockwiseInstruction : public Instruction
    {
    private:
        friend class Instructions;
        RotateClockwiseInstruction();
    public:

        void execute(const std::string& requester, RopeToy& rope, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr) const;
        void abort(const std::string& requester, RopeToy& rope) const;
    };
} // namespace Rope

#endif // ROPE_ROTATE_CLOCKWISE_INSTRUCTION_HPP