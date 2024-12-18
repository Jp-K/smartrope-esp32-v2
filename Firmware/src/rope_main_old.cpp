// #ifdef ROPE_MAIN

// #include <dependencies.h>

// #define ON HIGH
// #define OFF LOW

// #define BUTTON_GO_FORWARD 0
// #define BUTTON_TURN_RIGHT 1
// #define BUTTON_GO_BACKWARD 2
// #define BUTTON_TURN_LEFT 3
// #define BUTTON_EXECUTE 4

// using namespace Rope;

// Cpu cpu;
// Buzzer buzzer;
// Keypad keypad;
// Program program;
// Battery battery;
// MotorController motorController;

// void toggleLed(uint8_t led, uint8_t state)
// {
//     digitalWrite(led, state);
// }

// //==================================== SOUND =======================================//

// void playProgramFinishedFeedback()
// {
//     toggleLed(FRONT_LED_PIN, ON);
//     buzzer.play(Note::B, 6, 0.045f, 0.050f);
//     toggleLed(FRONT_LED_PIN, OFF);

//     toggleLed(RIGHT_LED_PIN, ON);
//     buzzer.play(Note::Db, 7, 0.045f, 0.050f);
//     toggleLed(RIGHT_LED_PIN, OFF);

//     toggleLed(BACK_LED_PIN, ON);
//     buzzer.play(Note::Eb, 7, 0.045f, 0.050f);
//     toggleLed(BACK_LED_PIN, OFF);

//     toggleLed(LEFT_LED_PIN, ON);
//     buzzer.play(Note::E, 7, 0.135f, 0.140f);
//     toggleLed(LEFT_LED_PIN, OFF);

//     toggleLed(FRONT_LED_PIN, ON);
//     buzzer.play(Note::E, 6, 0.135f);
//     toggleLed(FRONT_LED_PIN, OFF);
// }

// void playTurnOnFeedback()
// {
//     const float level = battery.readStatus().getLevel();

//     if (level >= battery.getCriticalLevel() && level < 0.50f)
//     {
//         toggleLed(FRONT_LED_PIN, ON);
//     }

//     else if (level >= 0.50f && level < 0.75f)
//     {
//         toggleLed(LEFT_LED_PIN, ON);
//         toggleLed(FRONT_LED_PIN, ON);
//     }
//     else if (level >= 0.75f && level < 0.90f)
//     {
//         toggleLed(LEFT_LED_PIN, ON);
//         toggleLed(BACK_LED_PIN, ON);
//         toggleLed(FRONT_LED_PIN, ON);
//     }
//     else if (level >= 0.90f)
//     {
//         toggleLed(LEFT_LED_PIN, ON);
//         toggleLed(BACK_LED_PIN, ON);
//         toggleLed(RIGHT_LED_PIN, ON);
//         toggleLed(FRONT_LED_PIN, ON);
//     }

//     delay(1000);

//     int8_t originalPitch = buzzer.getPitchVariation();

//     for (int i = 0; i <= 12; i+=1)
//     {
//         buzzer.play(Note::A, 6, 0.075f);
//         buzzer.setPitchVariation(originalPitch + i);
//     }
    
//     buzzer.setPitchVariation(originalPitch);

//     delay(1250);

//     toggleLed(LEFT_LED_PIN, OFF);
//     toggleLed(BACK_LED_PIN, OFF);
//     toggleLed(RIGHT_LED_PIN, OFF);
//     toggleLed(FRONT_LED_PIN, OFF);
// }

// void playWeakBatteryFeedback()
// {
//     const uint8_t LEDS[4] = {FRONT_LED_PIN, RIGHT_LED_PIN, BACK_LED_PIN, LEFT_LED_PIN};

//     int8_t originalPitch = buzzer.getPitchVariation();

//     for (int i = 0; i <= 12; i+=1)
//     {
//         uint8_t led = LEDS[i % 4];

//         toggleLed(led, ON);

//         buzzer.play(Note::A, 6, 0.075f);
//         buzzer.setPitchVariation(12 - i);

//         toggleLed(led, OFF);
//     }
    
//     buzzer.setPitchVariation(originalPitch);
// }

// void playExecuteFeedback()
// {
//     // toggleLed(FRONT_LED_PIN, ON);
//     // toggleLed(LEFT_LED_PIN, ON);
//     // toggleLed(BACK_LED_PIN, ON);
//     // toggleLed(RIGHT_LED_PIN, ON);
//     toggleLed(CENTER_LED_PIN, ON);
    
//     buzzer.play(Note::D, 7, 0.045f);
    
//     // toggleLed(FRONT_LED_PIN, OFF);
//     // toggleLed(LEFT_LED_PIN, OFF);
//     // toggleLed(BACK_LED_PIN, OFF);
//     // toggleLed(RIGHT_LED_PIN, OFF);
//     toggleLed(CENTER_LED_PIN, OFF);
// }

// void programCanceledFeedback()
// {
//     toggleLed(FRONT_LED_PIN, ON);
//     buzzer.play(Note::E, 7, 0.045f, 0.050f);
//     toggleLed(FRONT_LED_PIN, OFF);

//     toggleLed(RIGHT_LED_PIN, ON);
//     buzzer.play(Note::D, 7, 0.045f, 0.050f);
//     toggleLed(RIGHT_LED_PIN, OFF);

//     toggleLed(BACK_LED_PIN, ON);
//     buzzer.play(Note::C, 7, 0.045f, 0.050f);
//     toggleLed(BACK_LED_PIN, OFF);

//     toggleLed(LEFT_LED_PIN, ON);
//     buzzer.play(Note::Bb, 6, 0.135f);
//     toggleLed(LEFT_LED_PIN, OFF);
// }

// void turnOffAllLeds()
// {
//     toggleLed(RIGHT_LED_PIN, OFF);
//     toggleLed(LEFT_LED_PIN, OFF);
//     toggleLed(BACK_LED_PIN, OFF);
//     toggleLed(FRONT_LED_PIN, OFF);
//     toggleLed(CENTER_LED_PIN, OFF);
// }

// void setupButtonsLed()
// {
//     pinMode(RIGHT_LED_PIN, OUTPUT);
//     pinMode(LEFT_LED_PIN, OUTPUT);
//     pinMode(BACK_LED_PIN, OUTPUT);
//     pinMode(FRONT_LED_PIN, OUTPUT);
//     pinMode(CENTER_LED_PIN, OUTPUT);

//     turnOffAllLeds();
// }

// void afterWake()
// {
//     __debug__(Serial.println("Waking up"));
//     __debug__(Serial.flush());

//     // Wait until a button is pressed
//     keypad.listen();
// }

// void beforeSleep()
// {
//     turnOffAllLeds();

//     __debug__(Serial.println("Going to sleep"));
//     __debug__(Serial.println("Waiting for keypad events..."));
//     __debug__(Serial.flush());

//     while (true)
//     {
//         if (keypad.anyButtonPressed())
//         {
//             break;
//         }
//     }
    
// }

// bool executionCanceled()
// {
//     if (battery.readStatus().isCritical() || keypad.buttonPressed(BUTTON_EXECUTE, false))
//     {
//         program.cancel();
//         return true;
//     }

//     return false;
// }

// const float wheelPerimeter = Rope::Config::wheelsDiameter * PI;
// const float turningPerimeter = Rope::Config::distanceBetweenWheels * PI;
// const float stepDistance = wheelPerimeter / MotorController::StepsPerRevolution;

// uint32_t distanceToSteps(float distance)
// {
//     return round(distance / stepDistance);
// }

// void turn(float degrees)
// {
//     MotorController::Direction left[2] = {MotorController::Direction::Clockwise, MotorController::Direction::Clockwise};
//     MotorController::Direction right[2] = {MotorController::Direction::Counterclockwise, MotorController::Direction::Counterclockwise};

//     MotorController::Direction* directions = (degrees >= 0.0f)? right : left;

//     const float turningDistance = turningPerimeter * (fabs(degrees) / 360.0f);
//     const uint32_t turningSteps = distanceToSteps(turningDistance) + Rope::Config::deadZoneCorrection;

//     motorController.synchronizedMove(turningSteps, directions, Rope::Config::maxTurningSpeed, Rope::Config::turningCurve, executionCanceled);
// }

// void move(float distance)
// {
//     MotorController::Direction forward[2] = {MotorController::Direction::Counterclockwise, MotorController::Direction::Clockwise};
//     MotorController::Direction backward[2] = {MotorController::Direction::Clockwise, MotorController::Direction::Counterclockwise};

//     MotorController::Direction* directions = (distance >= 0.0f)? forward : backward;

//     const uint32_t movingSteps = distanceToSteps(fabs(distance)) + Rope::Config::deadZoneCorrection;
//     motorController.synchronizedMove(movingSteps, directions, Rope::Config::maxMovingSpeed, Rope::Config::movingCurve, executionCanceled);
// }

// void turnLeft()
// {
//     toggleLed(LEFT_LED_PIN, ON);    
//     buzzer.play(Note::C, 7, 0.045f, 0.050f);
//     buzzer.play(Note::As, 6, 0.045f, 0.050f);
//     buzzer.play(Note::A, 6, 0.135f);
//     turn(-90.0f);
//     toggleLed(LEFT_LED_PIN, OFF);
// }

// void turnRight()
// {
//     toggleLed(RIGHT_LED_PIN, ON);
//     buzzer.play(Note::A, 6, 0.045f, 0.050f);
//     buzzer.play(Note::As, 6, 0.045f, 0.050f);
//     buzzer.play(Note::C, 7, 0.135f);
//     turn(90.0f);
//     toggleLed(RIGHT_LED_PIN, OFF);
// }

// void moveBackward()
// {
//     toggleLed(BACK_LED_PIN, ON);
//     buzzer.play(Note::E, 7, 0.045f, 0.075f);
//     buzzer.play(Note::D, 7, 0.045f, 0.075f);
//     buzzer.play(Note::Cs, 7, 0.135f);
//     move(-Rope::Config::movingDistance);
//     toggleLed(BACK_LED_PIN, OFF);
// }

// void moveForward()
// {
//     toggleLed(FRONT_LED_PIN, ON);
//     buzzer.play(Note::Cs, 7, 0.045f, 0.075f);
//     buzzer.play(Note::D, 7, 0.045f, 0.075f);
//     buzzer.play(Note::E, 7, 0.135f);
//     move(Rope::Config::movingDistance);
//     toggleLed(FRONT_LED_PIN, OFF);
// }

// // This function is executed by the program after each instruction. This function can be used to add
// // a delay between the instructions

// void instructionExecuted(Program &program, const Program::Instruction instruction, const uint8_t index)
// {
//     for (uint16_t i = 0; i < Rope::Config::delayBetweenInstructions && !executionCanceled(); i++)
//     {
//         delayMicroseconds(1000);
//     }
// }

// // This function is automatically called by the program when it starts

// void programStarted(Program &program)
// {
//     __debug__(Serial.println("Program started"));
//     __debug__(Serial.flush());

//     playExecuteFeedback();
//     delay(500);
// }

// // This function is automatically called by the program when it terminates its
// // execution. A Program::Termination object is passed to the function allowing
// // us to detect how the program terminated

// void programTerminated(Program &program, const Program::Termination termination)
// {
//     __debug__(Serial.println("Program terminated"));
//     __debug__(Serial.flush());

//     if (termination == Program::Termination::Normal)
//     {
//         playProgramFinishedFeedback();
//     }
//     else if (termination == Program::Termination::Canceled)
//     {
//         programCanceledFeedback();
//     }

//     program.clear();
//     motorController.turnOff();
// }

// //================================== KEYPAD ======================================//

// bool addInstruction(const Program::Instruction instruction)
// {
//     if (!program.addInstruction(instruction))
//     {
//         programCanceledFeedback();
//         return false;
//     }

//     return true;
// }

// void forwardButtonAction()
// {
//     if (addInstruction(moveForward))
//     {
//         toggleLed(FRONT_LED_PIN, ON);
//         buzzer.play(Note::Cs, 7, 0.045f);
//         toggleLed(FRONT_LED_PIN, OFF);
//     }
// }

// void backwardButtonAction()
// {
//     if (addInstruction(moveBackward))
//     {
//         toggleLed(BACK_LED_PIN, ON);
//         buzzer.play(Note::E, 7, 0.045f);
//         toggleLed(BACK_LED_PIN, OFF);
//     }
// }

// void leftButtonAction()
// {
//     if (addInstruction(turnLeft))
//     {
//         toggleLed(LEFT_LED_PIN, ON);
//         buzzer.play(Note::C, 7, 0.045f);
//         toggleLed(LEFT_LED_PIN, OFF);
//     }
// }

// void rightButtonAction()
// {
//     if (addInstruction(turnRight))
//     {
//         toggleLed(RIGHT_LED_PIN, ON);
//         buzzer.play(Note::B, 6, 0.045f);
//         toggleLed(RIGHT_LED_PIN, OFF);
//     }
// }

// void executeButtonAction()
// {
//     if (!program.isEmpty())
//     {
//         program.execute();
//     }
//     else
//     {
//         __debug__(Serial.println("Program memory is empty, nothing to execute!!"));
//         __debug__(Serial.flush());

//         programCanceledFeedback();
//     }
// }

// void preventInteractions()
// {
//     for (uint8_t i = 1; i <= Config::batteryWarningRepetitions; i++)
//     {
//         playWeakBatteryFeedback();

//         for (uint8_t j = 1; j <= Config::delayBetweenBatteryWarnings; j++)
//         {
//             for (uint16_t k = 1; k <= 100; k++)
//             {
//                 Timer timer;
//                 timer.start();

//                 if (keypad.anyButtonPressed())
//                 {
//                     playWeakBatteryFeedback();
//                 }

//                 timer.waitFor(10, Timer::UnitOfTime::Milliseconds);
//             }
//         }        
//     }

//     cpu.sleep();
// }

// void waitForInteractions()
// {
//     cpu.sleep(beforeSleep, afterWake);
// }

// //=================================== MAIN =======================================//

// void dance()
// {
//     for (uint8_t i = 1; i < 3; i++)
//     {
//         Serial.println("Turn 1");
//         turn(22.5f);
//         Serial.println("Turn 2");
//         turn(-22.5f);
//         Serial.println("Turn 3");
//         turn(-22.5f);
//         Serial.println("Turn 4");
//         turn(22.5f);
//         Serial.println("Turn End");
//     }
// }

// void setup()
// {
//     __debug__(Serial.begin(SERIAL_SPEED));

//     buzzer.initialize(BUZZZER_PIN, Rope::Config::buzzerPitchVariation);
//     battery.initialize(BATTERY_PIN, Rope::Config::criticalBatteryLevel);
//     cpu.initialize(INTERRUPT_PIN);  
//     keypad.initialize(KEYPAD_PIN);
//     motorController.initialize();    
//     program.initialize(Rope::Config::programSize, programStarted, instructionExecuted, programTerminated);

//     keypad.registerButton(Range(1300, 1400), forwardButtonAction);
//     keypad.registerButton(Range(1600, 1700), rightButtonAction);
//     keypad.registerButton(Range(2000, 2100), backwardButtonAction);
//     keypad.registerButton(Range(2150, 2400), leftButtonAction);
//     keypad.registerButton(Range(3700, 3800), executeButtonAction);

//     // buzzer.setMuted(true);

//     Serial.println("1");

//     setupButtonsLed();

//     Serial.println("2");

//     pinMode(CHARGER_TOGGLE_PIN, HIGH);
//     //analogReference(DEFAULT);

//     Serial.println("3");

//     // dance();

//     Serial.println("4");

//     if (!battery.readStatus().isCritical())
//     {
//         Serial.println("5");
//         playTurnOnFeedback();
//     }

//     Serial.println("6");

//     // delay(5000);
    

//     // MotorController::Direction forward[2] = {MotorController::Direction::Counterclockwise, MotorController::Direction::Clockwise};
//     // MotorController::Direction* directions = forward;
//     // motorController.synchronizedMove(10000000, directions, Rope::Config::maxMovingSpeed, Rope::Config::movingCurve, executionCanceled);
// }

// void loop()
// {
//     // if (battery.readStatus().isCritical())
//     // {
//     //     preventInteractions();
//     // }
//     // else
//     // {
//     //     waitForInteractions();
//     // }    
//     moveForward();
//     delay(1000);
//     moveBackward();
//     delay(1000);
//     turnRight();
//     delay(1000);
//     turnLeft();
//     // delay(1000);
//     // moveBackward();
//     // delay(1000);
// }

// #endif // ROPE_MAIN