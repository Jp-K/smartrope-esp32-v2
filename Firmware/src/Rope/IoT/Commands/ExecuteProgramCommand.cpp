#include "Rope/IoT/Commands/ExecuteProgramCommand.hpp"

#include <string>
#include "Rope/RopeToy.hpp"

namespace Rope
{
    ExecuteProgramCommand::ExecuteProgramCommand(RopeToy& rope) : Command("EXECUTE_PROGRAM", rope)
    {
    }

    bool ExecuteProgramCommand::execute(const std::string& requester, const JsonObject& parameters) const
    {
        ExecutionParameters executionParameters = rope.program.getDefaultExecutionParameters();

        bool executeForever = parameters["forever"] | false;
        uint8_t repetitions = parameters["repetitions"] | 1;
        uint16_t instructionDelay = parameters["instructionDelay"] | executionParameters.getInstructionDelay();

        executionParameters.setExecuteForever(executeForever);
        executionParameters.setRepetitions(repetitions);
        executionParameters.setInstructionDelay(instructionDelay);

        rope.program.execute(requester);
        return true;
    }
}