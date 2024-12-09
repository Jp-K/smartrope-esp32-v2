#ifndef ROPE_ASYNC_ACTION_FINISH_HPP
#define ROPE_ASYNC_ACTION_FINISH_HPP

#include <string>
#include "Rope/Async/AsyncFinishMode.hpp"

namespace Rope
{
    class AsyncActionFinish
    {
    private:
        // friend class AsyncActionExecution;

        AsyncFinishMode finishMode;
        std::string errorMessage;
        std::string executionRequester;
        std::string abortionRequester;



    public:
        AsyncActionFinish();

        void reset();
        void setFinishMode(AsyncFinishMode finishMode);
        void setErrorMessage(const std::string& errorMessage);
        void setExecutionRequester(const std::string& executionRequester);
        void setAbortionRequester(const std::string& abortionRequester);

        AsyncFinishMode getFinishMode() const;
        const std::string& getErrorMessage() const;
        const std::string& getExecutionRequester() const;
        const std::string& getAbortionRequester() const;
    };
}

#endif // ROPE_ASYNC_ACTION_FINISH_HPP