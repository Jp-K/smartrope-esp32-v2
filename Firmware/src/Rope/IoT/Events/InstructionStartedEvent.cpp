#include "Rope/IoT/Events/InstructionStartedEvent.hpp"

namespace Rope
{
    InstructionStartedEvent::InstructionStartedEvent(const std::string& origin, const Instruction& instruction, uint16_t index, const MemoryState& memoryState, const ExecutionState& executionState) :
        Event("INSTRUCTION_STARTED", origin),
        instruction(&instruction),
        index(index),
        memoryState(memoryState),
        executionState(executionState)
    {

    }

    void InstructionStartedEvent::fillData(const JsonObject& data) const
    {
        data["instruction"] = instruction->getName();
        data["index"] = index;

        JsonObject execution = data.createNestedObject("execution");
        // JsonObject memory = data.createNestedObject("memory");

        // memoryState.toJson(memory.createNestedObject("currentState"));
        memoryState.toJson(data.createNestedObject("memory"));
        executionState.toJson(execution);
    }
}