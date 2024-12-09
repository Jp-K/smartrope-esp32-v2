#ifndef ROPE_IOT_KEYPAD_TUNED_EVENT_HPP
#define ROPE_IOT_KEYPAD_TUNED_EVENT_HPP

#include "Rope/IoT/Event.hpp"
#include "Rope/Keypad/KeypadParameters.hpp"

namespace Rope
{
    class KeypadTunedEvent : public Event
    {
    private:
        bool keypadIsOn;
        KeypadParameters parameters;

    public:
        KeypadTunedEvent(const std::string& origin, const KeypadParameters& parameters, bool keypadIsOn);
        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_KEYPAD_TUNED_EVENT_HPP