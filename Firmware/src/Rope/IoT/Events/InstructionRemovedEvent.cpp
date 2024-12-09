#include "Rope/IoT/Events/InstructionRemovedEvent.hpp"

namespace Rope
{
    InstructionRemovedEvent::InstructionRemovedEvent(const std::string& origin, const Instruction& instruction, uint16_t index, const MemoryState& previousState, const MemoryState& currentState) :
        InstructionEvent("INSTRUCTION_REMOVED", origin, instruction, index, previousState, currentState)
    {

    }

    void InstructionRemovedEvent::fillData(const JsonObject& data) const
    {
        InstructionEvent::fillData(data);
    }
}