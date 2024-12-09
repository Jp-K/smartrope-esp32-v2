#ifndef ROPE_KEYPAD_LEFT_BUTTON_HPP
#define ROPE_KEYPAD_LEFT_BUTTON_HPP

#include "Rope/Keypad/Button.hpp"

namespace Rope
{
    class LeftButton : public Button
    {
    public:
        LeftButton();
        void onPress(const std::string& requester, RopeToy& rope);
    };
}

#endif // ROPE_KEYPAD_LEFT_BUTTON_HPP