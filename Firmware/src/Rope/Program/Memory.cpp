#include "Rope/Program/Memory.hpp"

namespace Rope
{
    Memory::Memory(uint16_t initialMaxSize) : state(initialMaxSize), maxSize(initialMaxSize)
    {
        instructions.reserve(initialMaxSize);
    }

    bool Memory::isFull() const
    {
        return instructions.size() == maxSize;
    }

    bool Memory::isEmpty() const
    {
        return instructions.empty();
    }

    Instruction* Memory::insertInstruction(Instruction& instruction)
    {
        if (isFull())
        {
            return nullptr;
        }

        instructions.push_back(&instruction);
        state.registerInsertion();

        return &instruction;
    }

    Instruction* Memory::insertInstruction(Instruction& instruction, uint16_t index)
    {
        if (isFull() || indexOutOfBounds(index, true))
        {
            return nullptr;
        }

        instructions.insert(instructions.begin() + index, &instruction);
        state.registerInsertion();

        return &instruction;
    }

    Instruction* Memory::removeInstruction()
    {
        if (isEmpty())
        {
            return nullptr;
        }

        Instruction* instruction = instructions.back();

        instructions.pop_back();
        state.regsterRemoval();

        return instruction;
    }

    Instruction* Memory::removeInstruction(uint16_t index)
    {
        if (isEmpty() || indexOutOfBounds(index, false))
        {
            return nullptr;
        }

        Instruction* instruction = instructions[index];

        instructions.erase(instructions.begin() + index);
        state.regsterRemoval();

        return instruction;
    }

    Instruction* Memory::replaceInstruction(Instruction& instruction)
    {
        if (isEmpty())
        {
            return nullptr;
        }

        uint16_t index = getLastIndex();
        return replaceInstruction(instruction, index);
    }

    Instruction* Memory::replaceInstruction(Instruction& instruction, uint16_t index)
    {
        if (isEmpty() || indexOutOfBounds(index, false))
        {
            return nullptr;
        }

        instructions[index] = &instruction;
        state.registerUpdate();

        return &instruction;
    }

    void Memory::clear()
    {
        instructions.clear();
        state.registerCleaning();
    }

    bool Memory::resize(uint16_t newSize)
    {
        if (newSize == 0)
        {
            return false;
        }

        if (newSize > maxSize)
        {
            instructions.reserve(newSize);
            // Serial.printf("Getting bigger: %d\n", newSize);
        }
        else
        {
            instructions.resize(newSize);
            instructions.shrink_to_fit();
            // Serial.printf("Getting smaller: %d\n", newSize);
        }

        maxSize = newSize;
        state.registerResizing();
        // state.updateContent(instructions, newSize);

        return true;
    }

    MemoryState Memory::getState()
    {
        state.updateContent(instructions, maxSize);

        return state;
    }

    bool Memory::indexOutOfBounds(uint16_t index, bool inserting) const
    {
        if (index < 0)
        {
            return true;
        }

        if (inserting)
        {
            return index > instructions.size();
        }

        return index > getLastIndex();
    }

    Instruction* Memory::getInstruction(uint16_t index) const
    {
        if (isEmpty() || indexOutOfBounds(index, false))
        {
            return nullptr;
        }

        return instructions[index];
    }

    uint16_t Memory::getLastIndex() const
    {
        return instructions.size() - 1;
    }
}