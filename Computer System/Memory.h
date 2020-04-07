#pragma once

#include "Data.h"
#include <map>

namespace ownfos
{
	class Memory
	{
	public:
		void Print();
		void GUI();

		Data& operator[](unsigned int address);

		std::map<unsigned int, Data>::iterator begin();
		std::map<unsigned int, Data>::iterator end();

	private:
		InstructionEncoder encoder;
		InstructionFormatter formatter;
		std::map<unsigned int, Data> memory;
	};
}