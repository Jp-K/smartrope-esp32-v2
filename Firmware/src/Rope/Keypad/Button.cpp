#include "Rope/Keypad/Button.hpp"


#include "Rope/RopeToy.hpp"
#include "Rope/IoT/Events/ButtonPressedEvent.hpp"

namespace Rope
{
    Button::Button(const std::string& name, const Range& analogRange) :
        NamedEntity(name),
        analogRange(analogRange),
        states{ ButtonState::UP , ButtonState::UP }
    {

    }

    Range Button::getRange() const
    {
        return this->analogRange;
    }

    ButtonState Button::getPreviousState() const
    {
        return states[0];
    }

    ButtonState Button::getCurrentState() const
    {
        return states[1];
    }

    void Button::setCurrentState(ButtonState state)
    {
        states[0] = states[1];
        states[1] = state;
    }

    void Button::press(const std::string& requester, RopeToy& rope)
    {
        ButtonPressedEvent event(requester, *this);
        rope.IoT.notifyEvent(&event);
        
        onPress(requester, rope);
    }
} // namespace Rope
