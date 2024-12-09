#include "Rope/Util/BinaryString.hpp"


namespace Rope
{
    BinaryString::BinaryString(const std::string& str)
    {
        if (str.length() > 32)
        {
            this->str = str.substr(str.length() - 32, 32);
        }
        else
        {
            uint16_t pad = 32 - str.length();
            
            for (int i = 0; i < pad; i++)
            {
                this->str += '0';
            }

            this->str += str;
        }
    }

    BinaryString::BinaryString(uint32_t value)
    {
        for (uint8_t i = 0; i < 32; i++)
        {
            uint8_t bit = (value >> (31 - i)) & 0x00000001;

            if (bit == 0)
            {
                str += '0';
            }
            else if (bit == 1)
            {
                str += '1';
            }
        }
    }

    int32_t BinaryString::toInt()
    {
        return (int32_t)toUnsignedInt();
    }

    uint32_t BinaryString::toUnsignedInt()
    {
        uint32_t value = 0;

        for (uint16_t i = 0; i < 32; i++)
        {
            value = value << 1;
            char c = str[i];

            if (c == '1')
            {
                value += 1;
            }
        }

        return value;
    }

    bool BinaryString::isValid()
    {
        if (str.empty())
        {
            return false;
        }

        for (auto character : str)
        {
            if (character != '0' && character != '1')
            {
                return false;
            }
        }

        return true;
    }

    bool BinaryString::isInvalid()
    {
        return !isValid();
    }

    const std::string& BinaryString::toString()
    {
        return str;
    }
}