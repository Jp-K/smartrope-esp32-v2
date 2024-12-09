#ifndef ROPE_KEYPAD_BACK_BUTTON_HPP
#define ROPE_KEYPAD_BACK_BUTTON_HPP

#include "Rope/Keypad/Button.hpp"

namespace Rope
{
    class BackButton : public Button
    {
    public:
        BackButton();
        void onPress(const std::string& requester, RopeToy& rope);
    };
}

#endif // ROPE_KEYPAD_BACK_BUTTON_HPP