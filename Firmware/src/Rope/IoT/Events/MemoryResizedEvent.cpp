#include "Rope/IoT/Events/MemoryResizedEvent.hpp"

namespace Rope
{
    MemoryResizedEvent::MemoryResizedEvent(const std::string& origin, const MemoryState& previousState, const MemoryState& currentState) :
        MemoryChangedEvent("MEMORY_RESIZED", origin, previousState, currentState)
    {

    }

    void MemoryResizedEvent::fillData(const JsonObject& data) const
    {
        MemoryChangedEvent::fillData(data);
    }
}