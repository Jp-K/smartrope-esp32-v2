#include "Rope/IoT/Events/MemoryClearedEvent.hpp"

namespace Rope
{
    MemoryClearedEvent::MemoryClearedEvent(const std::string& origin, const MemoryState& previousState, const MemoryState& currentState) :
        MemoryChangedEvent("MEMORY_CLEARED", origin, previousState, currentState)
    {

    }

    void MemoryClearedEvent::fillData(const JsonObject& data) const
    {
        MemoryChangedEvent::fillData(data);
    }
}