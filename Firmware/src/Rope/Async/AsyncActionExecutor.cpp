// #include "Rope/Async/AsyncActionExecutor.hpp"

// #include "Rope/Util/Value.hpp"

// namespace Rope
// {
//     void AsyncActionExecutor::abort(const std::string& requester)
//     {
//         if (execution.isExecuting())
//         {
//             execution.abort(requester);

//             if (taskTimer)
//             {
//                 h4.finishNow(taskTimer);
//                 taskTimer = nullptr;
//             }
//         }
//     }

//     void AsyncActionExecutor::executeOnce(const std::string& requester, AsyncAction action, uint32_t delay, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr)
//     {
//         if (execution.isExecuting())
//         {
//             if (finishCallback)
//             {
//                 execution.fail("this action is already executing");
//                 finishCallback(execution.getActionFinish());
//             }

//             return;
//         }

//         delay = Value::highest((uint32_t)1, delay);

//         auto doTask = [this, &action]
//         {
//             if (execution.wasAborted())
//             {
//                 action(execution);
//             }
//         };

//         taskTimer = h4.once(delay, )

//             AsyncAction wrapper = [&action](AsyncActionExecution& execution)
//         {
//             action(execution);
//             execution.finish();
//         };

//         executeForever(requester, wrapper, delay, startCallback, finishCallback);
//     }



//     void AsyncActionExecutor::executeForever(const std::string& requester, AsyncAction action, uint32_t interval, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr)
//     {
//         if (execution.isExecuting())
//         {
//             if (finishCallback)
//             {
//                 execution.fail("this action is already executing");
//                 finishCallback(execution.getActionFinish());
//             }

//             return;
//         }

//         auto doTask = [this, requester, startCallback, finishCallback]()
//         {
//             execution.start(requester);

//             if (startCallback)
//             {
//                 startCallback(execution.getActionStart());
//             }
//         };

//         auto finish = [this, requester, finishCallback]()
//         {
//             executing = false;
//             taskTimer = nullptr;

//             if (finishCallback)
//             {
//                 finishCallback(FinishMode::Normal, requester, "");
//             }
//         };



//         taskTimer = h4.every(in, task, finish);
//     }
// }