
#include "Rope/IoT/IoTController.hpp"

#include <MQTTParams.h>
#include <UnitParams.h>
#include "Rope/RopeToy.hpp"

#define ERROR_PREFIX "IoTController error:"
#define INFO_PREFIX "IoTController:"

namespace Rope
{
    IoTController::IoTController(RopeToy& rope) :
        commands(rope)
    {

    }

    bool IoTController::topicIsInvalid(const std::vector<std::string>& vs) const
    {
        // H4Plugins will automatically remove the the device name/chip id and the "control"
        // segments from the topic path, so at this point the vector must have only 1 item,
        // which is the payload itself.
        //
        // Read more here:
        // https://github.com/philbowles/h4plugins/blob/master/docs/mqcmds.md#subscribedevice

        if (vs.size() != 1)
        {
            // h4pUserEvent(ERROR_PREFIX " invalid topic", NULL);
            return true;
        }

        return false;
    }

    DeserializationError IoTController::parseJson(const std::string& payload, JsonDocument& json) const
    {
        DeserializationError parseError = deserializeJson(json, payload);

        switch (parseError.code())
        {
        case DeserializationError::Ok:
            // h4pUserEvent(INFO_PREFIX " payload is a valid JSON and was parsed successfully", NULL);
            return parseError;

        case DeserializationError::EmptyInput:
            // h4pUserEvent(ERROR_PREFIX " the payload is empty", NULL);
            return parseError;

        case DeserializationError::IncompleteInput:
            // h4pUserEvent(ERROR_PREFIX " the payload is incomplete", NULL);
            return parseError;

        case DeserializationError::InvalidInput:
            // h4pUserEvent(ERROR_PREFIX " invalid JSON payload", NULL);
            return parseError;

        case DeserializationError::NoMemory:
            // h4pUserEvent(ERROR_PREFIX " not enough memory to parse the JSON", NULL);
            return parseError;

        case DeserializationError::TooDeep:
            // h4pUserEvent(ERROR_PREFIX " the JSON has too many nested levels", NULL);
            return parseError;
        }
    }

    void IoTController::executeCommands(const std::vector<std::string>& vs)
    {
        if (topicIsInvalid(vs))
        {
            return;
        }

        std::string combinedPayload;
        for (const auto& s : vs) {
            combinedPayload += s;
        }

        DynamicJsonDocument json(1024);

        if (parseJson(combinedPayload, json) != DeserializationError::Ok)
        {
            return;
        }

        if (json.is<JsonArray>())
        {
            return executeMultipleCommands(json.as<JsonArray>());
        }

        if (json.is<JsonObject>())
        {
            return executeSingleCommand(json.as<JsonObject>());
        }

        // h4pUserEvent(ERROR_PREFIX " this should not happen #1", NULL);
        return;
    }

    void IoTController::executeMultipleCommands(const JsonArray& jsonArray)
    {
        // H4_CMD_ERROR result = H4_CMD_OK;

        for (auto element : jsonArray)
        {
            if (element.is<JsonObject>())
            {
                executeSingleCommand(element.as<JsonObject>());
            }
        }

        return;
    }

    void IoTController::executeSingleCommand(const JsonObject& jsonObject)
    {
        std::string commandName = jsonObject["command"] | "";

        if (commandName.empty())
        {
            // h4pUserEvent(ERROR_PREFIX " invalid payload, property \"command\" is missing or is null", NULL);
            return;
        }

        Command* command = commands.withName(commandName);

        if (!command)
        {
            // h4pUserEvent(ERROR_PREFIX " command \"%s\" not found", commandName.c_str());
            return;
        }

        std::string requester = jsonObject["requester"] | "";

        if (requester.empty())
        {
            // h4pUserEvent(ERROR_PREFIX " invalid payload, property \"requester\" is missing os is null", NULL);
            return;
        }

        JsonVariant parameters = jsonObject["parameters"];

        if (parameters.is<JsonArray>())
        {
            return executeCommandMultipleTimes(command, requester, parameters.as<JsonArray>());
        }

        if (parameters.is<JsonObject>() || parameters.isNull())
        {
            return executeCommandOnce(command, requester, parameters.as<JsonObject>());
        }

        // h4pUserEvent(ERROR_PREFIX " this should not happen #2", NULL);
        return;
    }

    void IoTController::executeCommandMultipleTimes(Command* command, const std::string& requester, const JsonArray& parameters)
    {
        // H4_CMD_ERROR result = H4_CMD_OK;

        for (auto params : parameters)
        {
            if (params.is<JsonObject>())
            {
                executeCommandOnce(command, requester, params.as<JsonObject>());
            }
        }

        return;
    }

    void IoTController::executeCommandOnce(Command* command, const std::string& requester, const JsonObject& parameters)
    {
        if (command->execute(requester, parameters))
        {
            // h4pUserEvent(INFO_PREFIX " command \"%s\" executed", command->getName().c_str());
            return;
        }

        // h4pUserEvent(ERROR_PREFIX " invalid parameter for command \"%s\"", command->getName().c_str());
        return;
    }

    void IoTController::notifyEvent(const Event* event)
    {
        // if (!h4mqtt.connected())
        // {
            // h4pUserEvent(INFO_PREFIX " cannot notify event \"%s\", the mqtt connection is not stablished", event->getName().c_str());
        //     return;
        // }

        // h4pUserEvent(INFO_PREFIX " notifying event \"%s\"", event->getName().c_str());

        //DynamicJsonDocument root(1024);

        //root["id"] = event->getId();
        //root["timestamp"] = event->getTimestamp();
        //root["event"] = event->getName();
        //root["origin"] = event->getOrigin();

        //JsonObject data = root.createNestedObject("data");
        //event->fillData(data);

        //std::string payload;
        //serializeJson(root, payload);

        //uint32_t minDelay = 100;
        //uint32_t elapsed = millis() - lastSend;
        //int32_t remaining = minDelay - elapsed;

        //if (remaining <= 0) {
        //    h4pUserEvent(INFO_PREFIX " event payload: %s", payload.c_str());
        //    h4mqtt.xPublish(MQTT_EVENTS_TOPIC, payload, 2);
        //    lastSend = millis();
        //}
        //else {
        //    lastSend = millis() + remaining;
        //    h4.once(remaining, [this, payload] {
        //        h4pUserEvent(INFO_PREFIX " event payload: %s", payload.c_str());
        //        h4mqtt.xPublish(MQTT_EVENTS_TOPIC, payload, 2);
        //        });
        //}

    }

    void IoTController::sendIdentity(RopeToy& rope) const
    {
        //DynamicJsonDocument root(1024);

        //JsonObject unit = root.createNestedObject("unit");

        //unit["name"] = rope.config.unitName.get();
        //unit["description"] = rope.config.unitDescription.get();
        //unit["serialNumber"] = rope.config.unitSerialNumber.get();

        //JsonObject owner = root.createNestedObject("owner");

        //owner["name"] = rope.config.ownerName.get();
        //owner["phone"] = rope.config.ownerPhone.get();
        //owner["email"] = rope.config.ownerEmail.get();
        //owner["address"] = rope.config.ownerAddress.get();

        //std::string payload;
        //serializeJson(root, payload);

        //h4mqtt.xPublish(MQTT_IDENTITY_TOPIC, payload, 2, true);
    }

    void IoTController::sendOnlineStatus() const
    {
        //DynamicJsonDocument root(32);
        //root["status"] = "ONLINE";

        //std::string payload;
        //serializeJson(root, payload);

        //h4mqtt.xPublish(MQTT_STATUS_TOPIC, payload, 2, true);
    }
}