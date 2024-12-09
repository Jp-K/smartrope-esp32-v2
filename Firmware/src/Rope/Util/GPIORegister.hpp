#ifndef ROPE_GPIO_REGISTER_HPP
#define ROPE_GPIO_REGISTER_HPP

#include <stdint.h>
#include <string>

namespace Rope
{
    class GPIORegister
    {
    public:
        static constexpr uint32_t ALL_BITS = 0xFFFFFFFF;

        static uint32_t enable(uint32_t mask);
        static uint32_t enable(const std::string& mask);

        static uint32_t update(uint32_t mask, uint32_t value);
        static uint32_t update(uint32_t mask, const std::string& value);
        static uint32_t update(const std::string& mask, uint32_t value);
        static uint32_t update(const std::string& mask, const std::string& value);

        static uint32_t read();
    };
}

#endif // ROPE_GPIO_REGISTER_HPP