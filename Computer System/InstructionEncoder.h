#pragma once

#include "InstructionVisitor.h"
#include <optional>

namespace ownfos
{
	class Instruction;

	class InstructionEncoder : public InstructionVisitor
	{
	public:
		int operator()(const Instruction& instruction);

		virtual void Visit(const Move* move) override;
		virtual void Visit(const Jump* move) override;
		virtual void Visit(const Load* move) override;
		virtual void Visit(const Store* move) override;
		virtual void Visit(const Add* move) override;

	private:
		int encoded;
	};
}