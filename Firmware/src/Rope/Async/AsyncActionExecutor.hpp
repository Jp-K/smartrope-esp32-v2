// #ifndef ROPE_ASYNC_ACTION_EXECUTOR_HPP
// #define ROPE_ASYNC_ACTION_EXECUTOR_HPP

// #include <string>
// #include <H4.h>

// #include "Rope/Async/Async.hpp"

// namespace Rope
// {
//     class AsyncActionExecutor
//     {
//     public:

//     private:
//         AsyncActionExecution execution;
//         H4_TIMER taskTimer;

//     public:
//         AsyncActionExecutor();

//         void executeOnce(const std::string& requester, AsyncAction action, uint32_t delay, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr);
//         void executeForever(const std::string& requester, AsyncAction action, uint32_t interval, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr);

//         void abort(const std::string& requester);
//     };
// }

// #endif // ROPE_ASYNC_ACTION_EXECUTOR_HPP