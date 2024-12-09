#ifndef ROPE_KEYPAD_RIGHT_BUTTON_HPP
#define ROPE_KEYPAD_RIGHT_BUTTON_HPP

#include "Rope/Keypad/Button.hpp"

namespace Rope
{
    class RightButton : public Button
    {
    public:
        RightButton();
        void onPress(const std::string& requester, RopeToy& rope);
    };
}

#endif // ROPE_KEYPAD_RIGHT_BUTTON_HPP