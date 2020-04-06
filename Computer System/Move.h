#pragma once

#include "BinaryInstruction.h"

namespace ownfos
{
	class Move : public BinaryInstruction<unsigned int, unsigned int>
	{
	public:
		Move(unsigned int to, unsigned int from);

		virtual void Accept(InstructionVisitor* visitor) const override;
	};
}