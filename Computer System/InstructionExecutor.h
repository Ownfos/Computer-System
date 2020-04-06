#pragma once

#include "Data.h"
#include <vector>

namespace ownfos
{
	class Memory;

	class InstructionExecutor : public InstructionVisitor
	{
	public:
		InstructionExecutor(
			Memory& memory, 
			unsigned int initialProgramCounter = 0, 
			unsigned int registerCount = 4,
			unsigned int instructionStep = 1
		);

		void Execute();
		void Print();

		virtual void Visit(const Move* move) override;
		virtual void Visit(const Jump* move) override;
		virtual void Visit(const Load* move) override;
		virtual void Visit(const Store* move) override;
		virtual void Visit(const Add* move) override;

	private:
		Memory& memory;
		InstructionFormatter formatter;
		std::vector<Data> registers;
		Data instructionStep;
		Data programCounter;
		Data instruction;
		Data memoryBuffer;
		Data memoryAddress;
	};
}