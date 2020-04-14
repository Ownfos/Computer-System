#pragma once

#include "Instruction.h"

namespace ownfos
{
	template<typename T>
	class UnaryInstruction : public Instruction
	{
	public:
		UnaryInstruction(T operand)
			: operand(operand)
		{}

		T Operand() const
		{
			return operand;
		}

	private:
		T operand;
	};
}