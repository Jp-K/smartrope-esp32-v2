#include "Rope/IoT/Events/InstructionEvent.hpp"

namespace Rope
{
    InstructionEvent::InstructionEvent(const std::string& name, const std::string& origin, const Instruction& instruction, uint16_t index, const MemoryState& previousState, const MemoryState& currentState) :
        MemoryChangedEvent(name, origin, previousState, currentState),
        instruction(&instruction),
        index(index)
    {

    }

    void InstructionEvent::fillData(const JsonObject& data) const
    {
        data["instruction"] = instruction->getName();
        data["index"] = index;

        MemoryChangedEvent::fillData(data);
    }
}