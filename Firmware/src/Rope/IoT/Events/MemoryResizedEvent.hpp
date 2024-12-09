#ifndef ROPE_IOT_MEMORY_RESIZED_EVENT_HPP
#define ROPE_IOT_MEMORY_RESIZED_EVENT_HPP

#include "Rope/IoT/Events/MemoryChangedEvent.hpp"

namespace Rope
{
    class MemoryResizedEvent : public MemoryChangedEvent
    {
    public:
        MemoryResizedEvent(const std::string& origin, const MemoryState& currentState, const MemoryState& previousState);

        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_MEMORY_RESIZED_EVENT_HPP