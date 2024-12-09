#ifndef ROPE_IOT_PROGRAM_FINISHED_EVENT
#define ROPE_IOT_PROGRAM_FINISHED_EVENT

#include "Rope/IoT/Event.hpp"
#include "Rope/Program/MemoryState.hpp"
#include "Rope/Program/ExecutionState.hpp"
#include "Rope/Program/Program.hpp"
#include "Rope/Async/Async.hpp"

namespace Rope
{
    class ProgramFinishedEvent : public Event
    {
    private:
        AsyncFinishMode finishMode;
        MemoryState memoryState;
        ExecutionState executionState;

    public:
        ProgramFinishedEvent(const std::string& origin, AsyncFinishMode finishMode, const MemoryState& memoryState, const ExecutionState& executionState);
        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_PROGRAM_FINISHED_EVENT