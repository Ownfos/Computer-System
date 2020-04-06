#include "Store.h"
#include "InstructionVisitor.h"

namespace ownfos
{
	Store::Store(unsigned int to, unsigned int from)
		: BinaryInstruction(to, from)
	{}

	void Store::Accept(InstructionVisitor* visitor) const
	{
		visitor->Visit(this);
	}
}
