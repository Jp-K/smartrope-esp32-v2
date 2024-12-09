#ifndef ROPE_IOT_MEMORY_CLEARED_EVENT_HPP
#define ROPE_IOT_MEMORY_CLEARED_EVENT_HPP

#include "Rope/IoT/Events/MemoryChangedEvent.hpp"

namespace Rope
{
    class MemoryClearedEvent : public MemoryChangedEvent
    {
    public:
        MemoryClearedEvent(const std::string& origin, const MemoryState& previousState, const MemoryState& currentState);

        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_MEMORY_CLEARED_EVENT_HPP