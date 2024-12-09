// #include "Rope/Async/AsyncActionExecution.hpp"

// namespace Rope
// {
//     bool AsyncActionExecution::isExecuting() const
//     {
//         return executing;
//     }

//     bool AsyncActionExecution::hasFinished() const
//     {
//         return finished;
//     }

//     bool AsyncActionExecution::hasFailed() const
//     {
//         return failed;
//     }

//     bool AsyncActionExecution::wasAborted() const
//     {
//         return aborted;
//     }

//     void AsyncActionExecution::reset()
//     {
//         executing = false;
//         aborted = false;
//         finished = false;
//         failed = false;

//         startResult.reset();
//         finishResult.reset();
//     }

//     void AsyncActionExecution::start(const std::string& executionRequester)
//     {
//         reset();
//         executing = true;

//         startResult.setExecutionRequester(executionRequester);
//     }

//     void AsyncActionExecution::abort(const std::string& abortionRequester)
//     {
//         reset();
//         aborted = true;

//         finishResult.setFinishMode(AsyncFinishMode::Abortion);
//         finishResult.setAbortionRequester(abortionRequester);
//     }

//     void AsyncActionExecution::finish()
//     {
//         reset();
//         finished = true;

//         finishResult.setFinishMode(AsyncFinishMode::Normal);
//     }

//     void AsyncActionExecution::fail(const std::string& errorMessage)
//     {
//         reset();
//         failed = true;

//         finishResult.setFinishMode(AsyncFinishMode::Error);
//         finishResult.setErrorMessage(errorMessage);
//     }
// }