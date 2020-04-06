#include "InstructionDecoder.h"
#include "Constants.h"
#include "EveryInstruction.h"
#include <exception>

namespace ownfos
{
	std::unique_ptr<Instruction> InstructionDecoder::operator()(unsigned int instruction)
	{
		switch (instruction & Constants::INSTRUCTION_BITMASK)
		{
		case Constants::MOVE_BIT:
			return std::make_unique<Move>(
				(instruction & Constants::DOUBLE_OPERAND_FIRST_BITMASK) >> 12, 
				(instruction & Constants::DOUBLE_OPERAND_SECOND_BITMASK)
			);

		case Constants::JUMP_BIT:
			return std::make_unique<Jump>(instruction & Constants::SINGLE_OPERAND_BITMASK);

		case Constants::LOAD_BIT:
			return std::make_unique<Load>(
				(instruction & Constants::DOUBLE_OPERAND_FIRST_BITMASK) >> 12,
				(instruction & Constants::DOUBLE_OPERAND_SECOND_BITMASK)
			);

		case Constants::STORE_BIT:
			return std::make_unique<Store>(
				(instruction & Constants::DOUBLE_OPERAND_FIRST_BITMASK) >> 12,
				(instruction & Constants::DOUBLE_OPERAND_SECOND_BITMASK)
			);

		default:
			throw std::exception("Exception at InstructionDecoder::operator() - parameter was not an instruction");
		}
	}
}
