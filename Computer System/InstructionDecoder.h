#pragma once

#include <memory>

namespace ownfos
{
	class Instruction;

	class InstructionDecoder
	{
	public:
		std::unique_ptr<Instruction> operator()(unsigned int instruction);
	};
}