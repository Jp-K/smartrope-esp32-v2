#ifndef ROPE_IOT_INSTRUCTION_FINISHED_EVENT
#define ROPE_IOT_INSTRUCTION_FINISHED_EVENT

#include "Rope/IoT/Event.hpp"
#include "Rope/Program/MemoryState.hpp"
#include "Rope/Program/ExecutionState.hpp"

namespace Rope
{
    class InstructionFinishedEvent : public Event
    {
    private:
        const Instruction* instruction;
        uint16_t index;
        AsyncFinishMode finishMode;
        MemoryState memoryState;
        ExecutionState executionState;

    public:
        InstructionFinishedEvent(const std::string& origin, const Instruction& instruction, uint16_t index, AsyncFinishMode finishMode, const MemoryState& memoryState, const ExecutionState& executionState);
        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_INSTRUCTION_FINISHED_EVENT