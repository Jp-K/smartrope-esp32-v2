#ifndef ROPE_KEYPAD_FRONT_BUTTON_HPP
#define ROPE_KEYPAD_FRONT_BUTTON_HPP

#include "Rope/Keypad/Button.hpp"

namespace Rope
{
    class FrontButton : public Button
    {
    public:
        FrontButton();
        void onPress(const std::string& requester, RopeToy& rope);
    };
}

#endif // ROPE_KEYPAD_FRONT_BUTTON_HPP