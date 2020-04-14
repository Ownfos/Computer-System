#include "Load.h"
#include "InstructionVisitor.h"

namespace ownfos
{
	Load::Load(unsigned int to, unsigned int from)
		: BinaryInstruction(to, from)
	{}

	void Load::Accept(InstructionVisitor* visitor) const
	{
		visitor->Visit(this);
	}
}
