#ifndef ROPE_KEYPAD_HPP
#define ROPE_KEYPAD_HPP

#include <stdint.h>

#include "Rope/Keypad/KeypadParameters.hpp"
#include "Rope/Keypad/Buttons.hpp"
#include "Rope/Util/MovingAverage.hpp"
#include "Rope/Util/Timer.hpp"
#include "Rope/Common/NamedEntity.hpp"
#include "Rope/IoT/Events/KeypadTunedEvent.hpp"

namespace Rope
{
  class Keypad : NamedEntity
  {
  private:
    RopeToy& rope;

    uint8_t pin;

    Timer debounceTimer;
    Timer repeatTimer;

    bool canRepeat = false;
    
    TaskHandle_t listenTaskHandle = nullptr;

    Timer keypadRepeatDelayTimer;

    void startListening();
    void stopListening();
    void restart();

    void processClick(Button* button);

    void notifyKeypadTuned(const std::string& requester);

  public:
    Buttons buttons;

    KeypadParameters parameters;

    bool activeListening = false;

    Keypad(RopeToy& rope, uint8_t pin);

    void listen();

    bool isOn() const;
    bool isOff() const;

    void turnOn(const std::string& requester);
    void turnOff(const std::string& requester);

    KeypadParameters getKeypadParameters() const;
    void setKeypadParameters(const std::string& requester, const KeypadParameters& parameters);

    void initialize();
  };

} // namespace Rope

#endif // ROPE_KEYPAD_HPP