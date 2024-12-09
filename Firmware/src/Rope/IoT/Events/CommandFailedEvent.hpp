#ifndef ROPE_IOT_COMMAND_FAILED_EVENT
#define ROPE_IOT_COMMAND_FAILED_EVENT

#include "Rope/IoT/Event.hpp"

namespace Rope
{
    class CommandFailedEvent : public Event
    {
    private:
        std::string commandName;
        std::string reason;
    public:
        CommandFailedEvent(const std::string& origin, const std::string& commandName, const std::string& reason);
        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_COMMAND_FAILED_EVENT