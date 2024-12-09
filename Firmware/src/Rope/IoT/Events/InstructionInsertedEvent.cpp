#include "Rope/IoT/Events/InstructionInsertedEvent.hpp"

namespace Rope
{
    InstructionInsertedEvent::InstructionInsertedEvent(const std::string& origin, const Instruction& instruction, uint16_t index, const MemoryState& previousState, const MemoryState& currentState) :
        InstructionEvent("INSTRUCTION_INSERTED", origin, instruction, index, previousState, currentState)
    {

    }

    void InstructionInsertedEvent::fillData(const JsonObject& data) const
    {
        InstructionEvent::fillData(data);
    }
}