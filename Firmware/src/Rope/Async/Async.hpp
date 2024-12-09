#ifndef ROPE_ASYNC_HPP
#define ROPE_ASYNC_HPP

#include <functional>

#include "Rope/Async/AsyncActionExecution.hpp"
#include "Rope/Async/AsyncActionStart.hpp"
#include "Rope/Async/AsyncActionFinish.hpp"

namespace Rope
{

    // using AsyncAction = std::function<void(AsyncActionExecution& execution)>;
    using AsyncStartCallback = std::function<void(AsyncActionStart result)>;
    using AsyncFinishCallback = std::function<void(AsyncActionFinish result)>;
}

#endif // ROPE_ASYNC_HPP