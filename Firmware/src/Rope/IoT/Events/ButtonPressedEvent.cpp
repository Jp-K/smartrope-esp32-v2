#include "Rope/IoT/Events/ButtonPressedEvent.hpp"

namespace Rope
{
    ButtonPressedEvent::ButtonPressedEvent(const std::string& origin, const Button& button) :
        Event("BUTTON_PRESSED", origin),
        button(&button)
    {

    }

    void ButtonPressedEvent::fillData(const JsonObject& data) const
    {
        data["button"] = button->getName();
    }
}