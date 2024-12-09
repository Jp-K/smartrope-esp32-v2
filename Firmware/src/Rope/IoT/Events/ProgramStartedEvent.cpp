#include "Rope/IoT/Events/ProgramStartedEvent.hpp"
namespace Rope
{
    ProgramStartedEvent::ProgramStartedEvent(const std::string& origin, const MemoryState& memoryState, const ExecutionState& executionState) :
        Event("PROGRAM_STARTED", origin),
        memoryState(memoryState),
        executionState(executionState)
    {

    }

    void ProgramStartedEvent::fillData(const JsonObject& data) const
    {
        JsonObject execution = data.createNestedObject("execution");
        // JsonObject memory = data.createNestedObject("memory");

        // memoryState.toJson(memory.createNestedObject("currentState"));
        memoryState.toJson(data.createNestedObject("memory"));
        executionState.toJson(execution);
    }
}