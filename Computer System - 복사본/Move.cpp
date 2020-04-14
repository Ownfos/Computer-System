#include "Move.h"
#include "InstructionVisitor.h"

namespace ownfos
{
	Move::Move(unsigned int to, unsigned int from)
		: BinaryInstruction(to, from)
	{}

	void Move::Accept(InstructionVisitor* visitor) const
	{
		visitor->Visit(this);
	}
}
