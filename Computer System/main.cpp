#include "InstructionExecutor.h"
#include "Memory.h"
#include "Move.h"
#include "Jump.h"
#include "Load.h"
#include "Store.h"

using namespace ownfos;

#include <iostream>

int main()
{
	auto memory = Memory();
	auto cpu = InstructionExecutor(memory);

	// Memory block #1
	memory[0x0] = Move(1, 2);
	memory[0x1] = Jump(0x103);

	// Memory block #2
	memory[0x100] = 4;
	memory[0x101] = 3;
	memory[0x102] = 2;
	memory[0x103] = Store(0x100, 0);
	memory[0x104] = Load(2, 0x001);
	memory[0x105] = Move(0, 2);
	memory[0x106] = Jump(0x0);

	memory.Print();
	cpu.Print();

	for (auto i = 0; i < 10; i++)
		cpu.Execute();

	memory.Print();
	cpu.Print();
}