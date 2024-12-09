#ifndef ROPE_IOT_INSTRUCTION_REPLACED_EVENT_HPP
#define ROPE_IOT_INSTRUCTION_REPLACED_EVENT_HPP

#include "Rope/IoT/Events/InstructionEvent.hpp"

namespace Rope
{
    class InstructionReplacedEvent : public InstructionEvent
    {
    public:
        InstructionReplacedEvent(const std::string& origin, const Instruction& instruction, uint16_t index, const MemoryState& previousState, const MemoryState& currentState);

        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_INSTRUCTION_REPLACED_EVENT_HPP