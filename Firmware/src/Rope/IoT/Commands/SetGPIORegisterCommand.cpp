#include "Rope/IoT/Commands/SetGPIORegisterCommand.hpp"

#include "Rope/Util/BinaryString.hpp"
#include "Rope/Util/GPIORegister.hpp"

#define ERROR_PREFIX "%s error:"

namespace Rope
{
    SetGPIORegisterCommand::SetGPIORegisterCommand(RopeToy& rope) : Command("SET_GPIO_REGISTER", rope)
    {

    }

    bool SetGPIORegisterCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        std::string value = parameters["value"] | "null";
        std::string mask = parameters["mask"] | "null";

        BinaryString binaryMask(mask);

        if (binaryMask.isInvalid())
        {
            // h4pUserEvent(ERROR_PREFIX " the mask value is not a valid binary string: \"%s\"", getName().c_str(), mask.c_str());
            return false;
        }

        BinaryString binaryValue(value);

        if (binaryValue.isInvalid())
        {
            // h4pUserEvent(ERROR_PREFIX " the register value is not a valid binary string: \"%s\"", getName().c_str(), value.c_str());
            return false;
        }

        uint32_t maskUint = binaryMask.toUnsignedInt();
        uint32_t valueUint = binaryValue.toUnsignedInt();

        uint32_t previousValue = GPIORegister::read();
        uint32_t currentValue = GPIORegister::update(maskUint, valueUint);

        BinaryString binaryPrevious(previousValue);
        BinaryString binaryCurrent(currentValue);

        // h4pUserEvent("Mask:                   %s (%d)", binaryMask.toString().c_str(), maskUint);
        // h4pUserEvent("Value:                  %s (%d)", binaryValue.toString().c_str(), valueUint);

        // h4pUserEvent("Register before update: %s (%d)", binaryPrevious.toString().c_str(), previousValue);
        // h4pUserEvent("Register after update:  %s (%d)", binaryCurrent.toString().c_str(), currentValue);

        return true;
    }
}