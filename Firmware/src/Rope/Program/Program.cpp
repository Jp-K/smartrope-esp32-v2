#include "Rope/Program/Program.hpp"

#include <Arduino.h>

#include "Rope/RopeToy.hpp"
#include "Rope/Util/Value.hpp"

#include "Rope/IoT/Events/MemoryClearedEvent.hpp"
#include "Rope/IoT/Events/MemoryResizedEvent.hpp"

#include "Rope/IoT/Events/InstructionInsertedEvent.hpp"
#include "Rope/IoT/Events/InstructionRemovedEvent.hpp"
#include "Rope/IoT/Events/InstructionReplacedEvent.hpp"

#include "Rope/IoT/Events/InstructionStartedEvent.hpp"
#include "Rope/IoT/Events/InstructionFinishedEvent.hpp"

#include "Rope/IoT/Events/ProgramStartedEvent.hpp"
#include "Rope/IoT/Events/ProgramFinishedEvent.hpp"

namespace Rope
{
    Program::Program(RopeToy& rope) : NamedEntity("Program"),
        rope(rope),
        memory(rope.config.programSize.get())
    {

    }

    bool Program::isExecuting() const
    {
        return executing;
    }

    bool Program::cantModify() const
    {
        if (isExecuting())
        {
            // h4pUserEvent("%s error: can't modify the program while it's running", getName().c_str());
            return true;
        }

        return false;
    }

    bool Program::isEmpty()
    {
        return memory.getState().isEmpty();
    }

    void Program::clear(const std::string& requester)
    {
        if (cantModify())
        {
            return;
        }

        MemoryState previousState = memory.getState();
        memory.clear();
        MemoryState currentStatus = memory.getState();

        MemoryClearedEvent event(requester, previousState, currentStatus);
        rope.IoT.notifyEvent(&event);
    }

    void Program::resize(const std::string& requester, uint16_t newSize)
    {
        if (cantModify())
        {
            return;
        }

        uint16_t minSize = rope.config.minProgramSize.get();
        uint16_t maxSize = rope.config.maxProgramSize.get();

        newSize = Value::limit(newSize, minSize, maxSize, Value::Overflow::ChooseHighest);

        MemoryState previousState = memory.getState();

        if (memory.resize(newSize))
        {
            rope.config.programSize.set(newSize);
            MemoryState currentState = memory.getState();

            MemoryResizedEvent event(requester, previousState, currentState);
            rope.IoT.notifyEvent(&event);
        }
    }

    bool Program::insertInstruction(const std::string& requester, Instruction& instruction)
    {
        if (cantModify())
        {
            return false;
        }

        MemoryState previousState = memory.getState();

        if (memory.insertInstruction(instruction))
        {
            MemoryState currentState = memory.getState();
            uint16_t index = memory.getLastIndex();

            InstructionInsertedEvent event(requester, instruction, index, previousState, currentState);
            rope.IoT.notifyEvent(&event);

            return true;
        }

        return false;
    }

    bool Program::insertInstruction(const std::string& requester, Instruction& instruction, uint16_t index)
    {
        if (cantModify())
        {
            return false;
        }

        MemoryState previousState = memory.getState();

        if (memory.insertInstruction(instruction, index))
        {
            MemoryState currentState = memory.getState();

            InstructionInsertedEvent event(requester, instruction, index, previousState, currentState);
            rope.IoT.notifyEvent(&event);

            return true;
        }

        return false;
    }

    bool Program::removeInstruction(const std::string& requester)
    {
        if (cantModify())
        {
            return false;
        }

        MemoryState previousState = memory.getState();

        const Instruction* removedInstruction = memory.removeInstruction();

        if (removedInstruction)
        {
            MemoryState currentState = memory.getState();
            uint16_t index = memory.getLastIndex();

            InstructionRemovedEvent event(requester, *removedInstruction, index, previousState, currentState);
            rope.IoT.notifyEvent(&event);

            return true;
        }

        return false;
    }

    bool Program::removeInstruction(const std::string& requester, uint16_t index)
    {
        if (cantModify())
        {
            return false;
        }

        MemoryState previousState = memory.getState();

        const Instruction* removedInstruction = memory.removeInstruction(index);

        if (removedInstruction)
        {
            MemoryState currentState = memory.getState();

            InstructionRemovedEvent event(requester, *removedInstruction, index, previousState, currentState);
            rope.IoT.notifyEvent(&event);

            return true;
        }

        return false;
    }

    bool Program::replaceInstruction(const std::string& requester, Instruction& instruction)
    {
        if (cantModify())
        {
            return false;
        }

        MemoryState previousStatus = memory.getState();

        const Instruction* updatedInstruction = memory.replaceInstruction(instruction);

        if (updatedInstruction)
        {
            MemoryState currentStatus = memory.getState();
            uint16_t index = memory.getLastIndex();

            InstructionReplacedEvent event(requester, *updatedInstruction, index, previousStatus, currentStatus);
            rope.IoT.notifyEvent(&event);

            return true;
        }

        return false;
    }

    bool Program::replaceInstruction(const std::string& requester, Instruction& instruction, uint16_t index)
    {
        if (cantModify())
        {
            return false;
        }

        MemoryState previousStatus = memory.getState();

        const Instruction* updatedInstruction = memory.replaceInstruction(instruction, index);

        if (updatedInstruction)
        {
            MemoryState currentStatus = memory.getState();

            InstructionReplacedEvent event(requester, *updatedInstruction, index, previousStatus, currentStatus);
            rope.IoT.notifyEvent(&event);

            return true;
        }

        return false;
    }

    void Program::execute(const std::string& requester, AsyncStartCallback startCallback, AsyncFinishCallback finishCallback)
    {
        ExecutionParameters executionParameters = getDefaultExecutionParameters();
        execute(requester, executionParameters, startCallback, finishCallback);
    }

    void Program::execute(const std::string& requester, ExecutionParameters executionParameters, AsyncStartCallback startCallback, AsyncFinishCallback finishCallback)
    {
        if (isExecuting())
        {
            rope.playErrorFeedback();
            // h4pUserEvent("%s: the program is already executing", getName().c_str());

            if (finishCallback)
            {
                AsyncActionFinish result;
                result.setFinishMode(AsyncFinishMode::Error);
                finishCallback(result);
            }

            return;
        }

        if (memory.getState().isEmpty())
        {
            // h4pUserEvent("%s: the memory is empty", getName().c_str());
            rope.playErrorFeedback();

            if (finishCallback)
            {
                AsyncActionFinish result;
                result.setFinishMode(AsyncFinishMode::Error);
                finishCallback(result);
            }

            return;
        }

        executing = true;
        aborted = false;
        abortionRequester.clear();
        instructionTask = nullptr;

        executionState.setProgress(0.0f);
        executionState.registerStart();

        ProgramStartedEvent psEvent(requester, memory.getState(), executionState);
        rope.IoT.notifyEvent(&psEvent);

        AsyncFinishCallback programFinishCallback = [this, finishCallback](AsyncActionFinish finishResult)
        {
            Serial.println("entrou no finish callback");
            executing = false;
            aborted = false;
            abortionRequester.clear();
            currentInstruction = nullptr;
            instructionTask = nullptr;

            std::string finishRequester = (finishResult.getFinishMode() == AsyncFinishMode::Abortion) ? finishResult.getAbortionRequester() : finishResult.getExecutionRequester();

            if (finishResult.getFinishMode() == AsyncFinishMode::Abortion)
            {
                executionState.registerAbortion();
                rope.playErrorFeedback();
            }
            else
            {
                executionState.setProgress(100.0f);
                executionState.registerFinish();

                rope.leds.cycle(100);

                // tocar finalizou programa

                rope.sound.play(Event::Origin::Rope, Note::B, 6, 0.045f, 0.050f, nullptr, nullptr);
                rope.sound.play(Event::Origin::Rope, Note::Db, 7, 0.045f, 0.050f, nullptr, nullptr);
                rope.sound.play(Event::Origin::Rope, Note::Eb, 7, 0.045f, 0.050f, nullptr, nullptr);
                rope.sound.play(Event::Origin::Rope, Note::E, 7, 0.135f, 0.140f, nullptr, nullptr);
                rope.sound.play(Event::Origin::Rope, Note::E, 6, 0.045f, 0.135f, nullptr, nullptr);
            }

            ProgramFinishedEvent pfEvent(finishRequester, finishResult.getFinishMode(), memory.getState(), executionState);
            rope.IoT.notifyEvent(&pfEvent);

            clear(Event::Origin::Rope);

            if (finishCallback)
            {
                finishCallback(finishResult);
            }
        };

        uint16_t firstInstruction = 0;

        executeInstruction(requester, firstInstruction, executionParameters, programFinishCallback);
    }
    struct TaskParams
    {
        Program* program;
        std::string requester;
        uint16_t index;
        ExecutionParameters executionParameters;
        AsyncFinishCallback programFinishCallback;
    };

    void executeTask(void* param)
    {
        TaskParams* params = static_cast<TaskParams*>(param);
        Program* program = params->program;

        // Chamar doExecute
        auto doExecute = [program, params]()
        {
            if (program->aborted)
            {
                // vTaskDelete(NULL);
                return;
            }

            program->instructionTask = nullptr;
            program->currentInstruction = program->memory.getInstruction(params->index);

            if (!program->currentInstruction)
            {
                AsyncActionFinish result;
                result.setFinishMode(AsyncFinishMode::Normal);
                result.setExecutionRequester(params->requester);
                params->programFinishCallback(result);

                // vTaskDelete(NULL);
                return;
            }

            AsyncStartCallback instructionStarted = [program, params](AsyncActionStart result)
            {
                InstructionStartedEvent isEvent(params->requester, *program->currentInstruction, params->index, program->memory.getState(), program->executionState);
                program->rope.IoT.notifyEvent(&isEvent);
            };

            AsyncFinishCallback instructionFinished = [program, params](AsyncActionFinish result)
            {
                float progress = ((params->index + 1) / (program->memory.getState().getUsed() * 1.0f) * 100.f);
                program->executionState.setProgress(progress);

                InstructionFinishedEvent ifEvent(params->requester, *program->currentInstruction, params->index, result.getFinishMode(), program->memory.getState(), program->executionState);
                program->rope.IoT.notifyEvent(&ifEvent);

                program->currentInstruction = nullptr;

                if (result.getFinishMode() == AsyncFinishMode::Abortion)
                {
                    params->programFinishCallback(result);
                }
                else
                {
                    program->executeInstruction(params->requester, params->index + 1, params->executionParameters, params->programFinishCallback);
                }
            };
            Serial.println("prestes a executar");
            program->currentInstruction->execute(params->requester, program->rope, instructionStarted, instructionFinished);
        };

        // Chamar doFinish
        auto doFinish = [program, params]()
        {
            if (program->aborted)
            {
                AsyncActionFinish result;
                result.setFinishMode(AsyncFinishMode::Abortion);
                result.setAbortionRequester(program->abortionRequester);
                params->programFinishCallback(result);

                // vTaskDelete(NULL);
                return;
            }
        };
        Serial.println("antes do execute");
        doExecute();
        Serial.println("antes do finish");
        doFinish();
        Serial.println("*********");

        delete params;
        // vTaskDelete(NULL);
    }

    void Program::executeInstruction(const std::string& requester, uint16_t index, ExecutionParameters executionParameters, AsyncFinishCallback programFinishCallback)
    {
        if (instructionTask != nullptr)
        {
            vTaskDelete(instructionTask);
            instructionTask = nullptr;
        }

        uint16_t delay = rope.config.programInstructionDelay.get() / portTICK_PERIOD_MS;

        TaskParams* params = new TaskParams{this, requester, index, executionParameters, programFinishCallback};

        struct TaskParamsDelay {
            uint16_t delay;
            TaskParams* params;
        };

        TaskParamsDelay* param = new TaskParamsDelay{ delay, params };

        vTaskDelay(delay);
        executeTask(params);
        delete param;

        // xTaskCreatePinnedToCore(
        //     [](void* pvParameters) {

        //         TaskParamsDelay* param = static_cast<TaskParamsDelay*>(pvParameters);
        //         uint16_t delay = param->delay;
        //         TaskParams* params = param->params;

        //         vTaskDelay(delay);
        //         executeTask(params);

        //         delete param;
        //         vTaskDelete(NULL);
        //     },
        //     "InstructionTask",    
        //     4096,                 
        //     param,               
        //     1,                    
        //     &instructionTask,     
        //     1                     
        // );
    }

    void Program::abort(const std::string& requester)
    {
        if (isExecuting())
        {
            aborted = true;
            abortionRequester = requester;

            if (instructionTask)
            {
                vTaskDelete(instructionTask);
                instructionTask = nullptr;

                return;
            }

            if (currentInstruction)
            {
                currentInstruction->abort(abortionRequester, rope);
            }
        }
    }

    ExecutionParameters Program::getDefaultExecutionParameters() const
    {
        ExecutionParameters parameters(rope);

        parameters.setExecuteForever(false);
        parameters.setRepetitions(1);
        parameters.setInstructionDelay(rope.config.programInstructionDelay.get());
        return parameters;
    }

    ExecutionState Program::getExecutionState()
    {
        return executionState;
    }

    MemoryState Program::getMemoryState()
    {
        return memory.getState();
    }

} // namespace Rope
