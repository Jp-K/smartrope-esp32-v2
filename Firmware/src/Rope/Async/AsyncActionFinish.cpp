#include "Rope/Async/AsyncActionFinish.hpp"

namespace Rope
{
    AsyncActionFinish::AsyncActionFinish()
    {

    }

    void AsyncActionFinish::reset()
    {
        finishMode = AsyncFinishMode::Normal;
        errorMessage.clear();
        executionRequester.clear();
        abortionRequester.clear();
    }

    AsyncFinishMode AsyncActionFinish::getFinishMode() const
    {
        return finishMode;
    }

    void AsyncActionFinish::setFinishMode(AsyncFinishMode finishMode)
    {
        this->finishMode = finishMode;
    }

    const std::string& AsyncActionFinish::getErrorMessage() const
    {
        return errorMessage;
    }

    void AsyncActionFinish::setErrorMessage(const std::string& errorMessage)
    {
        this->errorMessage = errorMessage;
    }

    const std::string& AsyncActionFinish::getExecutionRequester() const
    {
        return executionRequester;
    }

    void AsyncActionFinish::setExecutionRequester(const std::string& executionRequester)
    {
        this->executionRequester = executionRequester;
    }

    const std::string& AsyncActionFinish::getAbortionRequester() const
    {
        return abortionRequester;
    }

    void AsyncActionFinish::setAbortionRequester(const std::string& abortionRequester)
    {
        this->abortionRequester = abortionRequester;
    }
}