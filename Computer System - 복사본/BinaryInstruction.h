#pragma once

#include "Instruction.h"

namespace ownfos
{
	template<typename T, typename U>
	class BinaryInstruction : public Instruction
	{
	public:
		BinaryInstruction(T operand1, U operand2)
			: operand1(operand1), operand2(operand2)
		{}

		T FirstOperand() const
		{
			return operand1;
		}

		U SecondOperand() const
		{
			return operand2;
		}

	private:
		T operand1;
		U operand2;
	};
}