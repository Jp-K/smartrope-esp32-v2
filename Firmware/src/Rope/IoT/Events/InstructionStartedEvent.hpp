#ifndef ROPE_IOT_INSTRUCTION_STARTED_EVENT
#define ROPE_IOT_INSTRUCTION_STARTED_EVENT

#include "Rope/IoT/Event.hpp"
#include "Rope/Program/MemoryState.hpp"
#include "Rope/Program/ExecutionState.hpp"

namespace Rope
{
    class InstructionStartedEvent : public Event
    {
    private:
        const Instruction* instruction;
        uint16_t index;
        MemoryState memoryState;
        ExecutionState executionState;

    public:
        InstructionStartedEvent(const std::string& origin, const Instruction& instruction, uint16_t index, const MemoryState& memoryState, const ExecutionState& executionState);
        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_INSTRUCTION_STARTED_EVENT