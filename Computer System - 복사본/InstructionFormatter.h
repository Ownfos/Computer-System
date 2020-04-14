#pragma once

#include "InstructionVisitor.h"
#include "InstructionDecoder.h"
#include <string>

namespace ownfos
{
	class Instruction;

	class InstructionFormatter : public InstructionVisitor
	{
	public:
		std::string operator()(const Instruction& instruction);

		virtual void Visit(const Move* move) override;
		virtual void Visit(const Jump* move) override;
		virtual void Visit(const Load* move) override;
		virtual void Visit(const Store* move) override;
		virtual void Visit(const Add* move) override;

	private:
		InstructionDecoder decoder;
		std::string formatted;
	};
}
