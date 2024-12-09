#include "Rope/IoT/Events/CommandFailedEvent.hpp"

namespace Rope
{
    CommandFailedEvent::CommandFailedEvent(const std::string& origin, const std::string& commandName, const std::string& reason) :
        Event("COMMAND_FAILED", origin),
        commandName(commandName),
        reason(reason)
    {

    }

    void CommandFailedEvent::fillData(const JsonObject& data) const
    {
        data["command"] = commandName;
        data["reason"] = reason;
    }
}