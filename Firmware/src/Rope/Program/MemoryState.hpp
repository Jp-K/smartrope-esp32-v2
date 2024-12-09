#ifndef ROPE_PROGRAM_MEMORY_STATE_HPP
#define ROPE_PROGRAM_MEMORY_STATE_HPP

#include <stdint.h>
#include <vector>
#include <ArduinoJson.h>
#include "Rope/Program/Instruction.hpp"

namespace Rope
{
    class MemoryState
    {
    private:
        friend class Memory;

        uint16_t size;
        uint16_t used;
        uint16_t free;

        uint16_t insertions = 0;
        uint16_t removals = 0;
        uint16_t updates = 0;
        uint16_t cleanings = 0;
        uint16_t resizings = 0;

        std::vector<Instruction*> content;

        void updateContent(const std::vector<Instruction*>& newContent, uint16_t newSize);
        void registerInsertion();
        void regsterRemoval();
        void registerUpdate();
        void registerCleaning();
        void registerResizing();

        MemoryState(uint16_t initialSize);

    public:
        bool isFull() const;
        bool isEmpty() const;

        uint16_t getSize() const;
        uint16_t getUsed() const;
        uint16_t getFree() const;
        uint16_t getInsertions() const;
        uint16_t getRemovals() const;
        uint16_t getUpdates() const;
        uint16_t getCleanings() const;
        uint16_t getResizings() const;

        const std::vector<Instruction*>& getContent() const;

        void toJson(const JsonObject& json) const;
    };
}

#endif // ROPE_PROGRAM_MEMORY_STATE_HPP