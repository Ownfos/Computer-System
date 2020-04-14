#pragma once

namespace ownfos
{
	class InstructionVisitor;

	class Instruction
	{
	public:
		virtual void Accept(InstructionVisitor* visitor) const = 0;
	};
}