#include "Rope/Program/MemoryState.hpp"

namespace Rope
{
    MemoryState::MemoryState(uint16_t initialSize) : size(initialSize), free(initialSize), used(0)
    {

    }

    bool MemoryState::isFull() const
    {
        return (free == 0);
    }

    bool MemoryState::isEmpty() const
    {
        return (used == 0);
    }

    uint16_t MemoryState::getSize() const
    {
        return size;
    }

    uint16_t MemoryState::getUsed() const
    {
        return used;
    }

    uint16_t MemoryState::getFree() const
    {
        return free;
    }

    uint16_t MemoryState::getInsertions() const
    {
        return insertions;
    }

    void MemoryState::registerInsertion()
    {
        insertions++;
    }

    uint16_t MemoryState::getRemovals() const
    {
        return removals;
    }

    void MemoryState::regsterRemoval()
    {
        removals++;
    }

    uint16_t MemoryState::getUpdates() const
    {
        return updates;
    }

    void MemoryState::registerUpdate()
    {
        updates++;
    }

    uint16_t MemoryState::getCleanings() const
    {
        return cleanings;
    }

    void MemoryState::registerCleaning()
    {
        cleanings++;
    }

    uint16_t MemoryState::getResizings() const
    {
        return resizings;
    }

    void MemoryState::registerResizing()
    {
        resizings++;
    }

    const std::vector<Instruction*>& MemoryState::getContent() const
    {
        return content;
    }

    void MemoryState::updateContent(const std::vector<Instruction*>& newContent, uint16_t newSize)
    {
        content = newContent;
        size = newSize;
        used = content.size();
        free = newSize - content.size();
    }

    void MemoryState::toJson(const JsonObject& state) const
    {
        state["size"] = size;
        state["used"] = used;
        state["free"] = free;
        state["insertions"] = insertions;
        state["removals"] = removals;
        state["updates"] = updates;
        state["cleanings"] = cleanings;
        state["resizings"] = resizings;
        state["full"] = isFull();
        state["empty"] = isEmpty();

        // JsonArray contentArray = state.createNestedArray("content");

        std::string contentAsString;

        contentAsString.reserve(content.size());

        for (auto instruction : content)
        {
            const std::string& name = instruction->getName();

            if (name == "MOVE_FORWARD")
            {
                contentAsString.append("F");
            }
            else if (name == "MOVE_BACKWARD")
            {
                contentAsString.append("B");
            }
            else if (name == "ROTATE_CLOCKWISE")
            {
                contentAsString.append("R");
            }
            else if (name == "ROTATE_COUNTERCLOCKWISE")
            {
                contentAsString.append("L");
            }
        }

        state["content"] = contentAsString;
    }
}