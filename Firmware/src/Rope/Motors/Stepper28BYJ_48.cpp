#include "Rope/Motors/Stepper28BYJ_48.hpp"


namespace Rope
{
    Stepper28BYJ_48::Stepper28BYJ_48(const std::string& name, uint8_t blueWire, uint8_t pinkWire, uint8_t yellowWire, uint8_t orangeWire, const std::string& wireSequence) :
        StepperMotor(name, std::vector<uint8_t>{blueWire, pinkWire, yellowWire, orangeWire}, halfStepAngle),
        blueWire(blueWire),
        pinkWire(pinkWire),
        yellowWire(yellowWire),
        orangeWire(orangeWire)
    {
        setWireSequence(wireSequence);
    }

    const std::string& Stepper28BYJ_48::getWireSequence() const
    {
        return wireSequence;
    }

    void Stepper28BYJ_48::setWireSequence(const std::string& wireSequence)
    {
        std::vector<uint8_t> pins;

        if (wireSequence.length() != 4)
        {
            // h4pUserEvent("Stepper28BYJ_48 error: wire sequence \"%s\" is invalid", wireSequence.c_str());
            return;
        }

        for (uint8_t i = 0; i < wireSequence.length(); i++)
        {
            char wire = wireSequence[i];

            switch (wire)
            {
            case 'B':
                pins.push_back(blueWire);
                continue;
            case 'P':
                pins.push_back(pinkWire);
                continue;
            case 'Y':
                pins.push_back(yellowWire);
                continue;
            case 'O':
                pins.push_back(orangeWire);
                continue;
            }
        }

        if (pins.size() != 4)
        {
            // h4pUserEvent("Stepper28BYJ_48 error: wire sequence \"%s\" is invalid", wireSequence.c_str());
            return;
        }

        setPins(pins);
    }
}