#ifndef ROPE_ASYNC_ACTION_START_HPP
#define ROPE_ASYNC_ACTION_START_HPP

#include <string>

namespace Rope
{
    class AsyncActionStart
    {
    private:
        // friend class AsyncActionExecution;

        std::string executionRequester;



    public:
        AsyncActionStart();

        void reset();
        void setExecutionRequester(const std::string& executionRequester);

        const std::string& getExecutionRequester() const;
    };
}

#endif // ROPE_ASYNC_ACTION_START_HPP