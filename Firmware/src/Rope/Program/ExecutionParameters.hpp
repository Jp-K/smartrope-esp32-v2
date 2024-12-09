#ifndef ROPE_EXECUTION_PARAMETERS_HPP
#define ROPE_EXECUTION_PARAMETERS_HPP

#include <stdint.h>

namespace Rope
{
    class RopeToy;
    class ExecutionParameters
    {
    private:
        friend class Program;
        RopeToy& rope;

        bool executeForever;
        uint8_t repetitions;
        uint16_t instructionDelay;

        ExecutionParameters(RopeToy& rope);

    public:
        uint8_t getRepetitions() const;
        void setRepetitions(const uint8_t repetitions);

        bool mustExecuteForever() const;
        void setExecuteForever(bool executeForever);

        uint16_t getInstructionDelay() const;
        void setInstructionDelay(uint16_t instructionDelay);
    };
}

#endif // ROPE_EXECUTION_PARAMETERS_HPP