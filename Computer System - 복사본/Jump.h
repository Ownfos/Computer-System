#pragma once

#include "UnaryInstruction.h"

namespace ownfos
{
	class Jump : public UnaryInstruction<unsigned int>
	{
	public:
		Jump(unsigned int destination);

		virtual void Accept(InstructionVisitor* visitor) const override;
	};
}