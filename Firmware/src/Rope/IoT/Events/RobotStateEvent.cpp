#include "Rope/IoT/Events/RobotStateEvent.hpp"

#include "Rope/RopeToy.hpp"

namespace Rope
{
    RobotStateEvent::RobotStateEvent(const std::string& origin, RopeToy& rope) :
        Event("ROBOT_STATE", origin),
        rope(rope)
    {

    }

    void RobotStateEvent::fillData(const JsonObject& data) const
    {
        JsonObject sound = data.createNestedObject("sound");
        PlaybackParameters soundParameters = rope.sound.getDefaultPlaybackParameters();

        sound["state"] = rope.sound.isOn() ? "ON" : "OFF";
        sound["playing"] = rope.sound.isPlaying();
        sound["volume"] = soundParameters.getVolume();
        sound["tempo"] = soundParameters.getTempo();
        sound["transposition"] = soundParameters.getTransposition();

        BatteryStatus batteryStatus = rope.battery.getStatus();
        std::string batteryState;

        if (batteryStatus.isFull())
        {
            batteryState = "FULL";
        }
        else if (batteryStatus.isEmpty())
        {
            batteryState = "EMPTY";
        }
        else if (batteryStatus.isCritical())
        {
            batteryState = "CRITICAL";
        }
        else
        {
            batteryState = "DISCHARGING";
        }

        JsonObject battery = data.createNestedObject("battery");

        battery["level"] = batteryStatus.getLevel();
        battery["state"] = batteryState;
        battery["critical_treshold"] = batteryStatus.getCriticalLevel();

        JsonObject voltage = battery.createNestedObject("voltage");

        voltage["volts"] = batteryStatus.getVoltage();
        voltage["millivolts"] = batteryStatus.getVoltageMillivolts();

        rope.program.isExecuting();

        JsonObject program = data.createNestedObject("program");
        JsonObject execution = program.createNestedObject("execution");
        // JsonObject memory = data.createNestedObject("memory");

        program["executing"] = rope.program.isExecuting();
        // rope.program.getMemoryState().toJson(memory.createNestedObject("currentState"));
        rope.program.getMemoryState().toJson(data.createNestedObject("memory"));
        rope.program.getExecutionState().toJson(execution);

        JsonObject leds = data.createNestedObject("leds");

        for (auto led : rope.leds.all())
        {
            leds[led->getName()]["state"] = led->isOn() ? "ON" : "OFF";
        }
    }
}