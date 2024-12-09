#include "Rope/IoT/Events/InstructionReplacedEvent.hpp"

namespace Rope
{
    InstructionReplacedEvent::InstructionReplacedEvent(const std::string& origin, const Instruction& instruction, uint16_t index, const MemoryState& previousState, const MemoryState& currentState) :
        InstructionEvent("INSTRUCTION_REPLACED", origin, instruction, index, previousState, currentState)
    {

    }

    void InstructionReplacedEvent::fillData(const JsonObject& data) const
    {
        InstructionEvent::fillData(data);
    }
}