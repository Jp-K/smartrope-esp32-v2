#ifndef ROPE_IOT_MEMORY_CHANGED_EVENT_HPP
#define ROPE_IOT_MEMORY_CHANGED_EVENT_HPP

#include "Rope/IoT/Event.hpp"
#include "Rope/Program/MemoryState.hpp"

namespace Rope
{
    class MemoryChangedEvent : public Event
    {
    private:
        MemoryState previousState;
        MemoryState currentState;

    public:
        MemoryChangedEvent(const std::string& name, const std::string& origin, const MemoryState& previousState, const MemoryState& currentState);

        virtual void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_MEMORY_CHANGED_EVENT_HPP