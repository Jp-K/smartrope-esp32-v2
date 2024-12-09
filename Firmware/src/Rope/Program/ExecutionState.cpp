#include "Rope/Program/ExecutionState.hpp"

#include <cmath>
#include "Rope/Util/Value.hpp"

namespace Rope
{

    ExecutionState::ExecutionState()
    {

    }

    void ExecutionState::reset()
    {
        progress = 0.0f;
        started = 0;
        finished = 0;
        aborted = 0;
    }

    void ExecutionState::setProgress(float progress)
    {
        progress = std::round(progress * 100.0f) / 100.0f;
        this->progress = Value::limit(progress, 0.0f, 100.0f);
    }

    void ExecutionState::registerStart()
    {
        started++;
    }

    void ExecutionState::registerFinish()
    {
        finished++;
    }

    void ExecutionState::registerAbortion()
    {
        aborted++;
    }

    float ExecutionState::getProgress() const
    {
        return progress;
    }

    uint16_t ExecutionState::getStarted() const
    {
        return started;
    }

    uint16_t ExecutionState::getFinished() const
    {
        return finished;
    }

    uint16_t ExecutionState::getAborted() const
    {
        return aborted;
    }

    void ExecutionState::toJson(const JsonObject& json) const
    {
        json["progress"] = progress;

        JsonObject statistics = json.createNestedObject("statistics");

        statistics["started"] = started;
        statistics["finished"] = finished;
        statistics["aborted"] = aborted;
    }
}
