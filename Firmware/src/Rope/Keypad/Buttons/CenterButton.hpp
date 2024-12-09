#ifndef ROPE_KEYPAD_CENTER_BUTTON_HPP
#define ROPE_KEYPAD_CENTER_BUTTON_HPP

#include "Rope/Keypad/Button.hpp"

namespace Rope
{
    class CenterButton : public Button
    {
    public:
        CenterButton();
        void onPress(const std::string& requester, RopeToy& rope);
    };
}

#endif // ROPE_KEYPAD_CENTER_BUTTON_HPP