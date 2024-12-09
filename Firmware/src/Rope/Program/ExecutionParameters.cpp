#include "Rope/Program/ExecutionParameters.hpp"

#include "Rope/RopeToy.hpp"
#include "Rope/Util/Value.hpp"

namespace Rope
{
    ExecutionParameters::ExecutionParameters(RopeToy& rope) : rope(rope)
    {

    }

    uint8_t ExecutionParameters::getRepetitions() const
    {
        return repetitions;
    }

    void ExecutionParameters::setRepetitions(const uint8_t repetitions)
    {
        uint8_t minRepetitions = 1;
        uint8_t maxRepetitions = rope.config.maxProgramRepetitions.get();

        this->repetitions = Value::limit(repetitions, minRepetitions, maxRepetitions);
    }

    bool ExecutionParameters::mustExecuteForever() const
    {
        return executeForever;
    }
        
    void ExecutionParameters::setExecuteForever(bool executeForever)
    {
        bool canExecuteForever = rope.config.programCanExecuteForever.get();
        
        this->executeForever = canExecuteForever && executeForever;
    }

    uint16_t ExecutionParameters::getInstructionDelay() const
    {
        return instructionDelay;
    }

    void ExecutionParameters::setInstructionDelay(uint16_t instructionDelay)
    {
        uint16_t minDelay = rope.config.minProgramInstructionDelay.get();
        uint16_t maxDelay = rope.config.maxProgramInstructionDelay.get();

        this->instructionDelay = Value::limit(instructionDelay, minDelay, maxDelay);
    }
}