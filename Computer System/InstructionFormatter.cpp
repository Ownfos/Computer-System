#include "InstructionFormatter.h"
#include "EveryInstruction.h"
#include "fmt/format.h"

namespace ownfos
{
	std::string InstructionFormatter::operator()(const Instruction& instruction)
	{
		instruction.Accept(this);
		return formatted;
	}

	void InstructionFormatter::Visit(const Move* move)
	{
		formatted = fmt::format("Move r{}, r{}", move->FirstOperand(), move->SecondOperand());
	}
	void InstructionFormatter::Visit(const Jump* jump)
	{
		formatted = fmt::format("Jump 0x{:0>8x}", jump->Operand());
	}
	void InstructionFormatter::Visit(const Load* load)
	{
		formatted = fmt::format("Load r{}, 0x{:0>8x}", load->FirstOperand(), load->SecondOperand());
	}
	void InstructionFormatter::Visit(const Store* store)
	{
		formatted = fmt::format("Store 0x{:0>8x}, r{}", store->FirstOperand(), store->SecondOperand());
	}
	void InstructionFormatter::Visit(const Add* add)
	{
	}
}