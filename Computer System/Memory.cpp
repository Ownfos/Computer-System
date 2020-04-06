#include "Memory.h"
#include "fmt/format.h"
#include <iostream>

namespace ownfos
{
	void Memory::Print()
	{
		std::cout << fmt::format("{:-^40}\n", "Memory");
		std::cout << fmt::format("{:^10} | {:^10} | {:^}\n", "address", "value(hex)", "value(decoded)");
		std::cout << fmt::format("{:-^40}\n", "");
		for (auto& [address, data] : memory)
		{
			std::cout << fmt::format("0x{:0>8x} | {} | {}\n", address, data.HexString(), data.DecodedString());
		}
	}

	Data& Memory::operator[](unsigned int address)
	{
		return memory[address];
	}
}