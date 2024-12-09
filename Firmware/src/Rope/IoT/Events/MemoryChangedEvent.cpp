#include "Rope/IoT/Events/MemoryChangedEvent.hpp"

namespace Rope
{
    MemoryChangedEvent::MemoryChangedEvent(const std::string& name, const std::string& origin, const MemoryState& previousState, const MemoryState& currentState) :
        Event(name, origin),
        previousState(previousState),
        currentState(currentState)
    {

    }

    void MemoryChangedEvent::fillData(const JsonObject& data) const
    {
        // JsonObject memory = data.createNestedObject("memory");

        // previousState.toJson(memory.createNestedObject("previousState"));
        // currentState.toJson(memory.createNestedObject("currentState"));

        currentState.toJson(data.createNestedObject("memory"));
    }
}