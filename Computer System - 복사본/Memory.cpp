#include "Memory.h"
#include "EveryInstruction.h"
#include "imgui.h"
#include "fmt/format.h"
#include <vector>
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

	void Memory::GUI()
	{
		auto parseHex = [](std::string buffer) { return std::stoi(buffer, 0, 16); };
		auto parseDec = [](std::string buffer) { return std::stoi(buffer); };

		ImGui::Begin("Memory");
		static std::string addressBuffer(20, '\0');
		ImGui::InputTextWithHint("Address", "0x123", &addressBuffer[0], addressBuffer.capacity());
		if (ImGui::Button("Allocate"))
		{
			memory[parseHex(addressBuffer)] = 0;
		}
		if (ImGui::TreeNodeEx("Memory content", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed))
		{
			static bool deleteRequest = false;
			static unsigned int deleteAddress = 0;
			static unsigned int hoveredAddress = 0xffffffff;
			for (auto& [address, data] : memory)
			{
				auto text = fmt::format("0x{:0>8x} : {}", address, data.DecodedString());
				if (hoveredAddress == address)
					ImGui::Text(text.c_str());
				else
					ImGui::TextDisabled(text.c_str());
				if (ImGui::IsItemHovered())
				{
					hoveredAddress = address;
				}
				if(ImGui::BeginPopupContextItem(("Delete popup" + std::to_string(address)).c_str()))
				{
					if (ImGui::Button(("Delete###" + std::to_string(address)).c_str()))
					{
						deleteRequest = true;
						deleteAddress = address;
						ImGui::CloseCurrentPopup();
					}

					ImGui::Separator();

					static std::vector<std::string> types = { "Value", "Move", "Jump", "Load", "Store" };
					static std::string selectedType = types[0];

					static std::string operand1Buffer(20, '\0');
					static std::string operand2Buffer(20, '\0');

					if (ImGui::BeginCombo("Type", selectedType.c_str()))
					{
						for (int i = 0; i < types.size(); ++i)
						{
							bool selected = (selectedType == types[i]);
							if (ImGui::Selectable(types[i].c_str(), &selected))
								selectedType = types[i];
							if (selected)
							{
								operand1Buffer.clear();
								operand2Buffer.clear();
								ImGui::SetItemDefaultFocus();
							}
						}
						ImGui::EndCombo();
					}

					if (selectedType == "Value")
					{
						ImGui::InputTextWithHint("New value", "12345", &operand1Buffer[0], operand1Buffer.capacity());
						if (ImGui::Button("Update"))
						{
							memory[address] = parseDec(operand1Buffer);
							ImGui::CloseCurrentPopup();
						}
					}
					else if (selectedType == "Move")
					{
						ImGui::InputTextWithHint("To (register)", "0", &operand1Buffer[0], operand1Buffer.capacity());
						ImGui::InputTextWithHint("From (register)", "1", &operand2Buffer[0], operand2Buffer.capacity());
						if (ImGui::Button("Update"))
						{
							memory[address] = Move(parseDec(operand1Buffer), parseDec(operand2Buffer));
							ImGui::CloseCurrentPopup();
						}
					}
					else if (selectedType == "Jump")
					{
						ImGui::InputTextWithHint("Address (memory)", "0x111", &operand1Buffer[0], operand1Buffer.capacity());
						if (ImGui::Button("Update"))
						{
							memory[address] = Jump(parseHex(operand1Buffer));
							ImGui::CloseCurrentPopup();
						}
					}
					else if (selectedType == "Load")
					{
						ImGui::InputTextWithHint("To (register)", "0", &operand1Buffer[0], operand1Buffer.capacity());
						ImGui::InputTextWithHint("From (memory)", "0x111", &operand2Buffer[0], operand2Buffer.capacity());
						if (ImGui::Button("Update"))
						{
							memory[address] = Load(parseDec(operand1Buffer), parseHex(operand2Buffer));
							ImGui::CloseCurrentPopup();
						}
					}
					else if (selectedType == "Store")
					{
						ImGui::InputTextWithHint("To (memory)", "0x111", &operand1Buffer[0], operand1Buffer.capacity());
						ImGui::InputTextWithHint("From (register)", "0", &operand2Buffer[0], operand2Buffer.capacity());
						if (ImGui::Button("Update"))
						{
							memory[address] = Store(parseHex(operand1Buffer), parseDec(operand2Buffer));
							ImGui::CloseCurrentPopup();
						}
					}
					ImGui::EndPopup();
				}
			}
			if (deleteRequest)
			{
				memory.erase(deleteAddress);
				deleteRequest = false;
			}
			ImGui::TreePop();
		}
		ImGui::End();
	}

	Data& Memory::operator[](unsigned int address)
	{
		return memory[address];
	}

	std::map<unsigned int, Data>::iterator Memory::begin()
	{
		return memory.begin();
	}

	std::map<unsigned int, Data>::iterator Memory::end()
	{
		return memory.end();
	}
}