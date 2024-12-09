#ifndef ROPE_IOT_INSTRUCTION_REMOVED_EVENT_HPP
#define ROPE_IOT_INSTRUCTION_REMOVED_EVENT_HPP

#include "Rope/IoT/Events/InstructionEvent.hpp"

namespace Rope
{
    class InstructionRemovedEvent : public InstructionEvent
    {
    public:
        InstructionRemovedEvent(const std::string& origin, const Instruction& instruction, uint16_t index, const MemoryState& previousState, const MemoryState& currentState);
        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_INSTRUCTION_REMOVED_EVENT_HPP