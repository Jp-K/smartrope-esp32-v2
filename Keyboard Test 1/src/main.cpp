#include <Arduino.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

#define key A4
#define INTERRUPT_PIN 2

#define RANGE_START 0
#define RANGE_END 1
#define LED_PIN 2
#define SAIDA_SOM 17

#define NO_BUTTON_PRESSED -1
#define BUTTON_FORWARD 0
#define BUTTON_RIGHT 1
#define BUTTON_BACKWARD 2
#define BUTTON_LEFT 3
#define BUTTON_EXECUTE 4

int buttons[5][3] = {
    {553, 636, 8},
    {803, 885, 7},
    {637, 719, 6},
    {720, 802, 5},    
    {886, 968, -1}
};

bool sound_off = false;
bool programando = true;
volatile bool interrupt_finished = false;

void feedback(int nota, int duracao)
{
  if(!sound_off){
    tone(SAIDA_SOM, nota);
    delay(duracao);
    noTone(SAIDA_SOM);
  }else{
    delay(duracao);
  }
}

void feedbackEsquerda(bool programando)
{
  switch (programando)
  {
    case true:
      feedback(440, 30);
      break;
    case false:
      feedback(440, 30);
      delay(50);
      feedback(660, 30);
      delay(50);
      feedback(880, 90);
      break;
    default:
      feedback(250, 250);
      break;
  }
}

void feedbackDireita(bool programando)
{
  switch (programando)
  {
    case true:
      feedback(440, 30);
      break;
    case false:
      feedback(440, 30);
      delay(50);
      feedback(660, 30);
      delay(50);
      feedback(880, 90);
      break;
    default:
      feedback(250, 250);
      break;
  }
}

void feedbackFrente(bool programando)
{
  switch (programando)
  {
    case true:
      feedback(880, 45);
      break;
    case false:
      feedback(880, 45);
      delay(75);
      feedback(1320, 45);
      delay(75);
      feedback(704, 135);
      break;
    default:                                                                                                                                                
      feedback(250, 250);
      break;
  }
}

void feedbackTras(bool programando)
{
  switch (programando)
  {
    case true:
      feedback(880, 45);
      break;
    case false:
      feedback(880, 45);
      delay(75);
      feedback(729, 45);
      delay(75);
      feedback(1056, 135);
      break;
    default:
      feedback(250, 250);
      break;
  }
}

void feedbackExecutar(bool programando)
{
  switch (programando)
  {
    case true:
      feedback(660, 45);
      digitalWrite(buttons[0][LED_PIN], HIGH);
      delay(50);
      digitalWrite(buttons[0][LED_PIN], LOW);
      delay(50);

      feedback(880, 45);
      digitalWrite(buttons[1][LED_PIN], HIGH);
      delay(50);
      digitalWrite(buttons[1][LED_PIN], LOW);
      delay(50);

      feedback(1100, 135);
      digitalWrite(buttons[2][LED_PIN], HIGH);
      delay(50);
      digitalWrite(buttons[2][LED_PIN], LOW);
      delay(50);

      feedback(880, 45);
      digitalWrite(buttons[3][LED_PIN], HIGH);
      delay(50);
      digitalWrite(buttons[3][LED_PIN], LOW);
      delay(50);

      break;
    case false:
      feedback(880, 45);
      delay(75);
      feedback(729, 45);
      delay(75);
      feedback(1056, 135);
      break;
    default:
      feedback(250, 250);
      break;
  }
}

int readPressedButton()
{
    int value = analogRead(key);

    if (value != 0)
    {
        delay(50);
        value = analogRead(key);
    }

    for (int i = 0; i < 5; i++)
    {
        int rangeStart = buttons[i][RANGE_START];
        int rangeEnd = buttons[i][RANGE_END];

        if (value >= rangeStart && value <= rangeEnd)
        {
            return i;
        }
    }

    return NO_BUTTON_PRESSED;
}

void turnOffAllLeds()
{
    for (int i = 0; i < 5; i++)
    {
        digitalWrite(buttons[i][LED_PIN], LOW);
    }
}

void setupButtonsLed()
{
    for (int i = 0; i < 5; i++)
    {
        int ledPin = buttons[i][LED_PIN];

        pinMode(ledPin, OUTPUT);
        digitalWrite(ledPin, LOW);
    }
}

void interruptDetected()
{
    Serial.println("Interrupcao");
    interrupt_finished = true;
}

void wakeUp()
{
    sleep_disable();

    power_all_enable();

    while (!interrupt_finished)
    {
    }

    interrupt_finished = false;

    Serial.print("Acordando");
    Serial.println("...");
    Serial.flush();

    delay(50);
}

void waitInterrupt()
{
    Serial.print("Entrando em stand by");
    Serial.println("...");
    Serial.flush();

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    power_all_disable();
    sleep_mode();
    wakeUp();
}

void readButtons()
{
    int pressedButton = readPressedButton();

    if (pressedButton == NO_BUTTON_PRESSED)
    {
        turnOffAllLeds();
        return;
    }

    if (buttons[pressedButton][LED_PIN] >= 0)
    {
        digitalWrite(buttons[pressedButton][LED_PIN], HIGH);
    }

    if (pressedButton == BUTTON_FORWARD)
    {
        Serial.println("Botao Pressionado: FRENTE");
        feedbackFrente(true);
    }
    else if (pressedButton == BUTTON_BACKWARD)
    {
        Serial.println("Botao Pressionado: TRAS");
        feedbackTras(true);
    }
    else if (pressedButton == BUTTON_LEFT)
    {
        Serial.println("Botao Pressionado: ESQUERDA");
        feedbackEsquerda(true);
    }
    else if (pressedButton == BUTTON_RIGHT)
    {
        Serial.println("Botao Pressionado: DIREITA");
        feedbackDireita(true);
    }
    else if (pressedButton == BUTTON_EXECUTE)
    {
        Serial.println("Botao Pressionado: EXECUTAR");
        feedbackExecutar(true);       
    }

    Serial.flush();
    while (readPressedButton() != NO_BUTTON_PRESSED)
    {
    }

    turnOffAllLeds();
}

void setup()
{
    Serial.begin(9600);

    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), interruptDetected, RISING);

    pinMode(key, INPUT);
    pinMode(INTERRUPT_PIN, INPUT);

    setupButtonsLed();
}

void loop()
{
    waitInterrupt();
    readButtons();    
}