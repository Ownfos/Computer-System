#include "Jump.h"
#include "InstructionVisitor.h"

namespace ownfos
{
	Jump::Jump(unsigned int destination)
		: UnaryInstruction(destination)
	{}

	void Jump::Accept(InstructionVisitor* visitor) const
	{
		visitor->Visit(this);
	}
}
