#include "Rope/Async/AsyncActionStart.hpp"

namespace Rope
{
    AsyncActionStart::AsyncActionStart()
    {

    }

    void AsyncActionStart::reset()
    {
        executionRequester.clear();
    }

    const std::string& AsyncActionStart::getExecutionRequester() const
    {
        return executionRequester;
    }

    void AsyncActionStart::setExecutionRequester(const std::string& executionRequester)
    {
        this->executionRequester = executionRequester;
    }
}