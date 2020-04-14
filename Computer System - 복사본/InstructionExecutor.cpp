#include "InstructionExecutor.h"
#include "EveryInstruction.h"
#include "Memory.h"
#include "imgui.h"
#include "fmt/format.h"
#include <iostream>

namespace ownfos
{
	InstructionExecutor::InstructionExecutor(
		Memory& memory, 
		unsigned int initialProgramCounter,
		unsigned int registerCount, 
		unsigned int instructionStep
	)
		: memory(memory), programCounter(initialProgramCounter),
		instructionStep(instructionStep), registers(registerCount),
		instruction(0), memoryAddress(0), memoryBuffer(0)
	{
	}

	void InstructionExecutor::Execute()
	{
		std::cout << fmt::format("{:-^40}\n", "Execution Cycle");
		instruction = memoryBuffer = memory[(memoryAddress = programCounter).AsValue()];
		programCounter += instructionStep;
		std::cout << fmt::format("Fetched and decoded instruction at {}\n", memoryAddress.HexString());
		std::cout << fmt::format("| {:<10} <- {}\n", "MAR", memoryAddress.HexString());
		std::cout << fmt::format("| {:<10} <- {} ({})\n", "MBR, IR", memoryBuffer.HexString(), memoryBuffer.DecodedString());
		std::cout << fmt::format("| {:<10} <- {}\n", "PC", programCounter.HexString());
		instruction.AsInstruction()->Accept(this);
	}

	void InstructionExecutor::Print()
	{
		std::cout << fmt::format("{:-^40}\n", "CPU");
		std::cout << fmt::format("{:^10} | {:^10} | {:^}\n", "register", "value(hex)", "value(decoded)");
		std::cout << fmt::format("{:-^40}\n", "");
		for (auto i = 0; i < registers.size(); ++i)
		{
			std::cout << fmt::format("r{:<9} | {} | {}\n", i, registers[i].HexString(), registers[i].DecodedString());
		}
		std::cout << fmt::format("{:<10} | {} |\n", "PC", programCounter.HexString());
		std::cout << fmt::format("{:<10} | {} | {}\n", "IR", instruction.HexString(), instruction.DecodedString());
		std::cout << fmt::format("{:<10} | {} |\n", "MAR", memoryAddress.HexString());
		std::cout << fmt::format("{:<10} | {} | {}\n", "MBR", memoryBuffer.HexString(), memoryBuffer.DecodedString());
	}

	void InstructionExecutor::GUI()
	{
		auto registerUpdatePopup = [&](Data& target, std::string id)
		{
			if (ImGui::BeginPopupContextItem(("Set general register###" + id).c_str()))
			{
				static std::string inputBuffer(20, '\0');
				ImGui::InputTextWithHint("New value", "0x12345678", &inputBuffer[0], inputBuffer.capacity());
				if (ImGui::Button("Update register"))
				{
					target = std::stoi(inputBuffer, 0, 16);
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
		};
		auto hoveredText = [&](std::string text, std::string id)
		{
			static std::string hoveredId = "";
			if (id == hoveredId)
			{
				ImGui::Text(text.c_str());
			}
			else
			{
				ImGui::TextDisabled(text.c_str());
				if (ImGui::IsItemHovered())
					hoveredId = id;
			}
		};

		ImGui::Begin("CPU");
		if (ImGui::Button(fmt::format("Execute next instruction [{}]", memory[programCounter.AsValue()].DecodedString()).c_str()))
		{
			Execute();
		}
		if (ImGui::TreeNodeEx("Register content", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed))
		{
			if (ImGui::TreeNodeEx("Modifiable", ImGuiTreeNodeFlags_DefaultOpen))
			{
				for (auto i = 0; i < registers.size(); ++i)
				{
					hoveredText(fmt::format("r{:<9} | {} | {}\n", i, registers[i].HexString(), registers[i].DecodedString()), std::to_string(i));
					registerUpdatePopup(registers[i], std::to_string(i));
				}
				hoveredText(fmt::format("{:<10} | {} |\n", "PC", programCounter.HexString()), "PC");
				registerUpdatePopup(programCounter, "PC");
				ImGui::TreePop();
			}
			if (ImGui::TreeNodeEx("Unmodifiable", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::TextDisabled(fmt::format("{:<10} | {} | {}\n", "IR", instruction.HexString(), instruction.DecodedString()).c_str());
				ImGui::TextDisabled(fmt::format("{:<10} | {} |\n", "MAR", memoryAddress.HexString()).c_str());
				ImGui::TextDisabled(fmt::format("{:<10} | {} | {}\n", "MBR", memoryBuffer.HexString(), memoryBuffer.DecodedString()).c_str());
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
		ImGui::End();
	}

	void InstructionExecutor::Visit(const Move* move)
	{
		auto to = move->FirstOperand();
		auto from = move->SecondOperand();
		registers[to] = registers[from];
		std::cout << fmt::format("Executed instruction {}\n", formatter(*move));
		std::cout << fmt::format("| r{:<9} <- {} ({})\n", to, registers[to].HexString(), registers[to].DecodedString());
	}

	void InstructionExecutor::Visit(const Jump* jump)
	{
		programCounter = { jump->Operand() };
		std::cout << fmt::format("Executed instruction {}\n", formatter(*jump));
		std::cout << fmt::format("| {:<10} <- {}\n", "PC", programCounter.HexString());
	}

	void InstructionExecutor::Visit(const Load* load)
	{
		auto to = load->FirstOperand();
		auto from = load->SecondOperand();
		memoryAddress = { from };
		registers[to] = memoryBuffer = memory[from];
		std::cout << fmt::format("Executed instruction {}\n", formatter(*load));
		std::cout << fmt::format("| {:<10} <- {}\n", "MAR", memoryAddress.HexString());
		std::cout << fmt::format("| {:<10} <- {} ({})\n", "MBR", memoryBuffer.HexString(), memoryBuffer.DecodedString());
		std::cout << fmt::format("| r{:<9} <- {} ({})\n", to, registers[to].HexString(), registers[to].DecodedString());
	}

	void InstructionExecutor::Visit(const Store* store)
	{
		auto to = store->FirstOperand();
		auto from = store->SecondOperand();
		memoryAddress = { to };
		memory[to] = memoryBuffer = registers[from];
		std::cout << fmt::format("Executed instruction {}\n", formatter(*store));
		std::cout << fmt::format("| {:<10} <- {}\n", "MAR", memoryAddress.HexString());
		std::cout << fmt::format("| {:<10} <- {} ({})\n", "MBR", memoryBuffer.HexString(), memoryBuffer.DecodedString());
		std::cout << fmt::format("| 0x{:0>8x} <- {} ({})\n", to, memory[to].HexString(), memory[to].DecodedString());
	}
	void InstructionExecutor::Visit(const Add* add)
	{
	}
}
