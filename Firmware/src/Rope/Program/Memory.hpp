#ifndef ROPE_PROGRAM_MEMORY_HPP
#define ROPE_PROGRAM_MEMORY_HPP

#include <vector>
#include <stdint.h>
#include "Rope/Program/MemoryState.hpp"
#include "Rope/Program/Instruction.hpp"

namespace Rope
{
    class Memory
    {
    private:
        std::vector<Instruction*> instructions;

        uint16_t maxSize = 0;
        MemoryState state;

        bool isFull() const;
        bool isEmpty() const;

        bool indexOutOfBounds(uint16_t index, bool inserting) const;

    public:
        Memory(uint16_t initialMaxSize);

        Instruction* insertInstruction(Instruction& instruction);
        Instruction* insertInstruction(Instruction& instruction, uint16_t index);

        Instruction* removeInstruction();
        Instruction* removeInstruction(uint16_t index);

        Instruction* replaceInstruction(Instruction& instruction);
        Instruction* replaceInstruction(Instruction& instruction, uint16_t index);

        Instruction* getInstruction(uint16_t index) const;

        void clear();
        bool resize(uint16_t newSize);

        MemoryState getState();
        
        uint16_t getLastIndex() const;
    };
}

#endif // ROPE_PROGRAM_MEMORY_HPP