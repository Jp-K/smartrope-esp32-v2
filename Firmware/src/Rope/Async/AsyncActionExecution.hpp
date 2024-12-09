// #ifndef ROPE_ASYNC_ACTION_EXECUTION_HPP
// #define ROPE_ASYNC_ACTION_EXECUTION_HPP

// #include <stdint.h>
// #include <string>

// #include "Rope/Async/AsyncActionStart.hpp"
// #include "Rope/Async/AsyncActionFinish.hpp"

// namespace Rope
// {
//     class AsyncActionExecution
//     {
//     private:
//         friend class AsyncActionExecutor;

//         bool executing = false;
//         bool finished = false;
//         bool failed = false;
//         bool aborted = false;

//         AsyncActionStart startResult;
//         AsyncActionFinish finishResult;

//         bool isExecuting() const;
//         bool hasFinished() const;
//         bool hasFailed() const;
//         bool wasAborted() const;

//         void reset();
//         void start(const std::string& executionRequester);
//         void abort(const std::string& abortionRequester);

//         const AsyncActionStart& getActionStart() const;
//         const AsyncActionFinish& getActionFinish() const;

//         AsyncActionExecution();

//     public:
//         void finish();
//         void fail(const std::string& errorMessage);
//     };
// }

// #endif // ROPE_ASYNC_ACTION_EXECUTION_HPP