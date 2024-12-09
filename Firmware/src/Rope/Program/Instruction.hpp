#ifndef ROPE_PROGRAM_INSTRUCTION_HPP
#define ROPE_PROGRAM_INSTRUCTION_HPP

#include "Rope/Common/NamedEntity.hpp"
#include "Rope/Async/Async.hpp"

namespace Rope
{
    class RopeToy;
    class Instruction : public NamedEntity
    {
    public:
        Instruction(const std::string& name);

        virtual void execute(const std::string& requester, RopeToy& rope, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr) const = 0;
        virtual void abort(const std::string& requester, RopeToy& rope) const = 0;
    };
} // namespace Rope

#endif // ROPE_PROGRAM_INSTRUCTION_HPP