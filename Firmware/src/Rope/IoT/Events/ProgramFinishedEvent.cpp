#include "Rope/IoT/Events/ProgramFinishedEvent.hpp"

namespace Rope
{
    ProgramFinishedEvent::ProgramFinishedEvent(const std::string& origin, AsyncFinishMode finishMode, const MemoryState& memoryState, const ExecutionState& executionState) :
        Event("PROGRAM_FINISHED", origin),
        finishMode(finishMode),
        memoryState(memoryState),
        executionState(executionState)
    {

    }

    void ProgramFinishedEvent::fillData(const JsonObject& data) const
    {
        data["finishMode"] = (finishMode == AsyncFinishMode::Abortion) ? "ABORTED" : "NORMAL";

        JsonObject execution = data.createNestedObject("execution");
        // JsonObject memory = data.createNestedObject("memory");

        // memoryState.toJson(memory.createNestedObject("currentState"));
        memoryState.toJson(data.createNestedObject("memory"));
        executionState.toJson(execution);
    }
}