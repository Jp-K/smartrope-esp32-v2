#ifndef ROPE_UTIL_VALUE_HPP
#define ROPE_UTIL_VALUE_HPP

#include <stdint.h>
#include <Arduino.h>

namespace Rope
{
    class Value
    {
    public:
        enum class Overflow : uint8_t
        {
            ChooseClosest,
            ChooseLowest,
            ChooseHighest,
            ChooseMean
        };

        // The function names must be enclosed in parentheses because there are
        // Arduino macros with the same names. Enclosing the names in parentheses
        // prevents the macro expansion as discussed here:
        //
        // https://stackoverflow.com/questions/1543736/how-do-i-temporarily-disable-a-macro-expansion-in-c-c

        template <class T>
        static T lowest(T a, T b)
        {
            return (a < b) ? a : b;
        }

        template <class T>
        static T highest(T a, T b)
        {
            return (a > b) ? a : b;
        }

        template <class T>
        static T limit(T value, T min, T max, Overflow overflow = Overflow::ChooseClosest)
        {
            if (value < min || value > max)
            {
                switch (overflow)
                {
                case Overflow::ChooseLowest:
                    return min;
                case Overflow::ChooseHighest:
                    return max;
                case Overflow::ChooseClosest:
                    value = Value::highest(value, min);
                    value = Value::lowest(value, max);
                    return value;
                case Overflow::ChooseMean:
                    return (max + min) / ((T) 2);
                }
            }

            return value;
        }
    };
}

#endif // ROPE_UTIL_VALUE_HPP