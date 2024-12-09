#ifndef ROPE_IOT_INSTRUCTION_EVENT_HPP
#define ROPE_IOT_INSTRUCTION_EVENT_HPP

#include "Rope/IoT/Event.hpp"
#include "Rope/IoT/Events/MemoryChangedEvent.hpp"
#include "Rope/Program/Instruction.hpp"
namespace Rope
{
    class InstructionEvent : public MemoryChangedEvent
    {
    private:
        const Instruction* instruction;
        uint16_t index;

    public:
        InstructionEvent(const std::string& name, const std::string& origin, const Instruction& instruction, uint16_t index, const MemoryState& previousState, const MemoryState& currentState);
        virtual void fillData(const JsonObject& data) const;
    };
}

#endif // ROPE_IOT_INSTRUCTION_EVENT_HPP