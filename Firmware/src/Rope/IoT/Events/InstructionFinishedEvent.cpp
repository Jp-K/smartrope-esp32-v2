#include "Rope/IoT/Events/InstructionFinishedEvent.hpp"

namespace Rope
{
    InstructionFinishedEvent::InstructionFinishedEvent(const std::string& origin, const Instruction& instruction, uint16_t index, AsyncFinishMode finishMode, const MemoryState& memoryState, const ExecutionState& executionState) :
        Event("INSTRUCTION_FINISHED", origin),
        instruction(&instruction),
        index(index),
        finishMode(finishMode),
        memoryState(memoryState),
        executionState(executionState)
    {

    }

    void InstructionFinishedEvent::fillData(const JsonObject& data) const
    {
        data["finishMode"] = (finishMode == AsyncFinishMode::Abortion) ? "ABORTED" : "NORMAL";

        data["instruction"] = instruction->getName();
        data["index"] = index;

        JsonObject execution = data.createNestedObject("execution");
        // JsonObject memory = data.createNestedObject("memory");

        // memoryState.toJson(memory.createNestedObject("currentState"));
        memoryState.toJson(data.createNestedObject("memory"));
        executionState.toJson(execution);
    }
}