#ifndef ROPE_UTIL_BINARY_STRING_HPP
#define ROPE_UTIL_BINARY_STRING_HPP

#include <string>

namespace Rope
{
    class BinaryString
    {
    private:
        std::string str;
    public:
        BinaryString(const std::string& str);
        BinaryString(uint32_t value);

        int32_t toInt();
        uint32_t toUnsignedInt();
        bool isValid();
        bool isInvalid();
        const std::string& toString();
    };
}

#endif // ROPE_UTIL_HPP