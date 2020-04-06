#include "Data.h"
#include "Instruction.h"
#include "fmt/format.h"

namespace ownfos
{
	Data::Data(unsigned int value)
		: type(DataType::Value), data(value)
	{}

	Data::Data(const Instruction & instruction)
		: type(DataType::Instruction), data(encoder(instruction))
	{}

	Data& Data::operator+=(const Data& other)
	{
		data += other.data;
		return *this;
	}

	std::string Data::DecodedString()
	{
		if(type == DataType::Value)
			return std::to_string(data);
		if(type == DataType::Instruction)
			return formatter(*AsInstruction());
	}

	std::string Data::HexString()
	{
		return fmt::format("0x{:0>8x}", data);
	}

	unsigned int Data::AsValue() const
	{
		return data;
	}

	std::unique_ptr<Instruction> Data::AsInstruction()
	{
		return decoder(data);
	}
}
