#ifndef ROPE_IOT_CONTROLLER_HPP
#define ROPE_IOT_CONTROLLER_HPP

#include <vector>
#include <string>

#include <ArduinoJson.h>

#include "Rope/IoT/Commands.hpp"
#include "Rope/IoT/Event.hpp"

namespace Rope
{
    class RopeToy;
    class IoTController
    {
    private:

        uint32_t lastSend = 0;

        Commands commands;

        bool topicIsInvalid(const std::vector<std::string>& vs) const;
        DeserializationError parseJson(const std::string& payload, JsonDocument& json) const;

        void executeMultipleCommands(const JsonArray& jsonArray);
        void executeSingleCommand(const JsonObject& jsonObject);

        void executeCommandMultipleTimes(Command* command, const std::string& requester, const JsonArray& parameters);
        void executeCommandOnce(Command* command, const std::string& requester, const JsonObject& parameters);

        std::string getOnlineStatusJson(bool online) const;
        void setLastWill() const;

    public:
        IoTController(RopeToy& ropeToy);

        void executeCommands(const std::vector<std::string>& vs);

        void notifyEvent(const Event* event);

        void sendIdentity(RopeToy& rope) const;
        void sendOnlineStatus() const;
        // void notifyCommandFailed(const std::string& requester, const std::string& commandName, const std::string &reason);
    };
}

#endif // ROPE_IOT_CONTROLLER_HPP