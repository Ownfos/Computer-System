#pragma once

#include "BinaryInstruction.h"

namespace ownfos
{
	class Load : public BinaryInstruction<unsigned int, unsigned int>
	{
	public:
		Load(unsigned int to, unsigned int from);

		virtual void Accept(InstructionVisitor* visitor) const override;
	};
}