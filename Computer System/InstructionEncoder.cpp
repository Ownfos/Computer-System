#include "InstructionEncoder.h"
#include "Constants.h"
#include "EveryInstruction.h"

namespace ownfos
{
	int InstructionEncoder::operator()(const Instruction& instruction)
	{
		instruction.Accept(this);
		return encoded;
	}

	void InstructionEncoder::Visit(const Move* move)
	{
		auto firstOperandBits = move->FirstOperand() << 12;
		auto secondOperandBits = move->SecondOperand();
		encoded = Constants::MOVE_BIT | firstOperandBits | secondOperandBits;
	}

	void InstructionEncoder::Visit(const Jump* jump)
	{
		encoded = Constants::JUMP_BIT | jump->Operand();
	}

	void InstructionEncoder::Visit(const Load* load)
	{
		auto firstOperandBits = load->FirstOperand() << 12;
		auto secondOperandBits = load->SecondOperand();
		encoded = Constants::LOAD_BIT | firstOperandBits | secondOperandBits;
	}

	void InstructionEncoder::Visit(const Store* store)
	{
		auto firstOperandBits = store->FirstOperand() << 12;
		auto secondOperandBits = store->SecondOperand();
		encoded = Constants::STORE_BIT | firstOperandBits | secondOperandBits;
	}

	void InstructionEncoder::Visit(const Add* add)
	{
	}
}
