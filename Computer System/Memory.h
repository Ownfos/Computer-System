#pragma once

#include "Data.h"
#include <map>

namespace ownfos
{
	class Memory
	{
	public:
		void Print();

		Data& operator[](unsigned int address);

	private:
		InstructionEncoder encoder;
		InstructionFormatter formatter;
		std::map<unsigned int, Data> memory;
	};
}