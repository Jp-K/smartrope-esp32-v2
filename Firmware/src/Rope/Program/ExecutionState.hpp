#ifndef ROPE_PROGRAM_EXECUTION_STATE_HPP
#define ROPE_PROGRAM_EXECUTION_STATE_HPP

#include <stdint.h>
#include <ArduinoJson.h>

namespace Rope
{
    class ExecutionState
    {
    private:
        friend class Program;

        float progress;
        uint16_t started;
        uint16_t finished;
        uint16_t aborted;

    public:
        float getProgress() const;
        uint16_t getStarted() const;
        uint16_t getFinished() const;
        uint16_t getAborted() const;

        ExecutionState();

        void setProgress(float progress);
        void registerStart();
        void registerFinish();
        void registerAbortion();

        void reset();

        void toJson(const JsonObject& json) const;
    };
}

#endif // ROPE_PROGRAM_EXECUTION_STATE_HPP