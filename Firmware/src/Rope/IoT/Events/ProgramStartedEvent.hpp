#ifndef ROPE_IOT_PROGRAM_STARTED_EVENT
#define ROPE_IOT_PROGRAM_STARTED_EVENT

#include "Rope/IoT/Event.hpp"
#include "Rope/Program/MemoryState.hpp"
#include "Rope/Program/ExecutionState.hpp"

namespace Rope
{
    class ProgramStartedEvent : public Event
    {
    private:
        MemoryState memoryState;
        ExecutionState executionState;
        
    public:
        ProgramStartedEvent(const std::string& origin, const MemoryState& memoryState, const ExecutionState& executionState);
        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_PROGRAM_STARTED_EVENT