#ifndef ROPE_KEYPAD_BUTTON_HPP
#define ROPE_KEYPAD_BUTTON_HPP

#include <string>
#include <stdint.h>

#include "Rope/Util/Range.hpp"
#include "Rope/Common/NamedEntity.hpp"

namespace Rope
{
  enum class ButtonState : uint8_t
  {
    UP = 0,
    DOWN = 1
  };

  class RopeToy;
  class Button: public NamedEntity
  {
  private:
    Range analogRange;
    ButtonState states[2];

  protected:
    virtual void onPress(const std::string& requester, RopeToy& rope) = 0;

  public:
    Button(const std::string& name, const Range& analogRange);

    virtual Range getRange() const final;

    ButtonState getPreviousState() const;
    ButtonState getCurrentState() const;
    void setCurrentState(ButtonState state);

    virtual void press(const std::string& requester, RopeToy& rope) final;
  };

} // namespace Rope

#endif // ROPE_KEYPAD_BUTTON_HPP