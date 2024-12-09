#ifndef ROPE_KEYPAD_BUTTONS_HPP
#define ROPE_KEYPAD_BUTTONS_HPP

#include <vector>
#include <string>

#include "Rope/Common/NamedEntityContainer.hpp"
#include "Rope/Keypad/Button.hpp"
#include "Rope/Keypad/Buttons/FrontButton.hpp"
#include "Rope/Keypad/Buttons/RightButton.hpp"
#include "Rope/Keypad/Buttons/BackButton.hpp"
#include "Rope/Keypad/Buttons/LeftButton.hpp"
#include "Rope/Keypad/Buttons/CenterButton.hpp"

namespace Rope
{
    class Buttons : public NamedEntityContainer<Button>
    {
    public:
        FrontButton front;
        RightButton right;
        BackButton back;
        LeftButton left;
        CenterButton center;

        Buttons() : NamedEntityContainer("Buttons")
        {
            addEntity(front);
            addEntity(right);
            addEntity(back);
            addEntity(left);
            addEntity(center);
        }
    };
}

#endif // ROPE_KEYPAD_BUTTONS_HPP