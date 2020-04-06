#pragma once

#include "BinaryInstruction.h"

namespace ownfos
{
	class Store : public BinaryInstruction<unsigned int, unsigned int>
	{
	public:
		Store(unsigned int to, unsigned int from);

		virtual void Accept(InstructionVisitor* visitor) const override;
	};
}