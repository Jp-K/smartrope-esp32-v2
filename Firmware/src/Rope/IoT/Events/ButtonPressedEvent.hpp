#ifndef ROPE_IOT_BUTTON_PRESSED_EVENT
#define ROPE_IOT_BUTTON_PRESSED_EVENT

#include "Rope/IoT/Event.hpp"
#include "Rope/Keypad/Button.hpp"

namespace Rope
{
    class ButtonPressedEvent : public Event
    {
    private:
        const Button* button;
    public:
        ButtonPressedEvent(const std::string& origin, const Button& button);
        void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_BUTTON_PRESSED_EVENT