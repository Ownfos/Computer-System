#pragma once

#include "InstructionEncoder.h"
#include "InstructionDecoder.h"
#include "InstructionFormatter.h"

namespace ownfos
{
	enum class DataType
	{
		Value,
		Instruction
	};

	class Data
	{
	public:
		Data() = default;
		Data(unsigned int value);
		Data(const Instruction& instruction);
		Data(const Data& other) = default;

		Data& operator=(const Data& other) = default;
		Data& operator+=(const Data& other);

		std::string DecodedString();
		std::string HexString();

		unsigned int AsValue() const;
		std::unique_ptr<Instruction> AsInstruction();

	private:
		InstructionEncoder encoder;
		InstructionDecoder decoder;
		InstructionFormatter formatter;

		DataType type = DataType::Value;
		unsigned int data = 0;
	};
}

