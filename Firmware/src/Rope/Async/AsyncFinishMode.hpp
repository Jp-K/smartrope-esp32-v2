#ifndef ROPE_ASYNC_FINISH_MODE_HPP
#define ROPE_ASYNC_FINISH_MODE_HPP

#include <stdint.h>

namespace Rope
{
    enum class AsyncFinishMode : uint8_t
    {
        Normal,
        Abortion,
        Error
    };
}

#endif // ROPE_ASYNC_FINISH_MODE_HPP