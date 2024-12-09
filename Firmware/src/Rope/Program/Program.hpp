#ifndef ROPE_PROGRAM_HPP
#define ROPE_PROGRAM_HPP

#include <stdint.h>
#include <string>
#include <vector>


#include "Rope/Program/Instruction.hpp"
#include "Rope/Program/Instructions.hpp"
#include "Rope/Program/ExecutionParameters.hpp"
#include "Rope/Program/ExecutionState.hpp"
#include "Rope/Program/Memory.hpp"
#include "Rope/Common/NamedEntity.hpp"

namespace Rope
{
  class RopeToy;
  class Program : public NamedEntity
  {
  private:

  public:
    Instructions instructions;

    bool executing = false;
    bool aborted = false;

    std::string abortionRequester;
    Instruction* currentInstruction;
    TaskHandle_t instructionTask = nullptr;
    ExecutionState executionState;

    Memory memory;

    RopeToy& rope;

    Program(RopeToy& rope);

    void executeInstruction(const std::string& requester, uint16_t index, ExecutionParameters executionParameters, AsyncFinishCallback finishCallback);

    bool isExecuting() const;
    bool isEmpty();
    bool cantModify() const;

    void clear(const std::string& requester);
    void resize(const std::string& requester, uint16_t size);

    bool insertInstruction(const std::string& requester, Instruction& instruction);
    bool insertInstruction(const std::string& requester, Instruction& instruction, uint16_t index);

    bool removeInstruction(const std::string& requester);
    bool removeInstruction(const std::string& requester, uint16_t index);

    bool replaceInstruction(const std::string& requester, Instruction& instruction);
    bool replaceInstruction(const std::string& requester, Instruction& instruction, uint16_t index);

    void execute(const std::string& requester, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr);
    void execute(const std::string& requester, ExecutionParameters executionParameters, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr);
    void abort(const std::string& requester);

    void resetStatistics(const std::string& requester);

    ExecutionParameters getDefaultExecutionParameters() const;

    ExecutionState getExecutionState();
    MemoryState getMemoryState();
  };

} // namespace Rope

#endif // ROPE_PROGRAM_HPP