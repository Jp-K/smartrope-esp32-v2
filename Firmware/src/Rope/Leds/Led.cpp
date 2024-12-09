#include "Rope/Leds/Led.hpp"

#include <Arduino.h>

#include "Rope/RopeToy.hpp"
#include "Rope/IoT/Events/LedToggledEvent.hpp"

namespace Rope
{
   Led::Led(RopeToy& rope, const std::string& name, uint8_t pin) : NamedEntity(name),
      rope(rope),
      pin(pin)
   {
      pinMode(pin, OUTPUT);
      turnOff(Event::Origin::Rope);
   }

   bool Led::isOn() const
   {
      return on;
   }

   bool Led::isOff() const
   {
      return !on;
   }

   void Led::turnOn(const std::string& requester)
   {
      digitalWrite(pin, HIGH);
      on = true;

      notifyToggle(requester);
   };

   void Led::turnOff(const std::string& requester)
   {
      digitalWrite(pin, LOW);
      on = false;

      notifyToggle(requester);
   }

   void Led::toggle(const std::string& requester)
   {
      if (on)
      {
         turnOff(requester);
      }
      else
      {
         turnOn(requester);
      }
   }

   void Led::setState(const std::string& requester, uint8_t state)
   {
      if (state == HIGH)
      {
         turnOn(requester);
      }
      else if (state == LOW)
      {
         turnOff(requester);
      }
   }


   //void Led::blinkOnce(const std::string& requester, uint32_t intervalOn)
   //{
   //   turnOn(requester);
   //   h4.once(intervalOn, [this, requester] { turnOff(requester); });
   //}
   struct TurnOffTaskParams
   {
      Led* led;
      std::string requester;
      uint32_t intervalOn;
   };

   void turnOffTask(void *param)
   {
      TurnOffTaskParams* params = static_cast<TurnOffTaskParams*>(param);
      vTaskDelay(params->intervalOn / portTICK_PERIOD_MS);
      params->led->turnOff(params->requester);
      //vTaskDelete(NULL);
   }

   void Led::blinkOnce(const std::string& requester, uint32_t intervalOn)
   {
      Serial.println("antes do turn on");
      turnOn(requester);
      Serial.println("depois do turn on");

      TurnOffTaskParams* params = new TurnOffTaskParams{this, requester, intervalOn};

      // xTaskCreatePinnedToCore(
      //    turnOffTask,                   
      //    "TurnOffLedTask",             
      //    2048,                    
      //    params,                    
      //    1,                          
      //    NULL,                     
      //    1                         
      // );
      Serial.println("antes do turn off");
      turnOffTask(params);
      Serial.println("depois do turn off");
   }

   void Led::notifyToggle(const std::string& requester)
   {
      LedToggledEvent event(requester, this);
      rope.IoT.notifyEvent(&event);
   }
} // namespace Rope
