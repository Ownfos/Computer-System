#include "Parameters.h"
#include "Selector.h"
#include "fmt/format.h"

namespace ownfos
{
    void ValueParameter::SelectWithUI(Registers& registers, Memory& memory)
    {
        ImGui::InputInt(("Value###" + std::to_string(reinterpret_cast<int>(this))).c_str(), &value);
    }

    unsigned int ValueParameter::SelectedItem() 
    { 
        return value; 
    }

    void AddressParameter::SelectWithUI(Registers& registers, Memory& memory)
    {
        if (memory.find(selectedAddress) == memory.end())
            selectedAddress = memory.begin()->first;

        Selector(
            "Address###" + std::to_string(reinterpret_cast<int>(this)),
            selectedAddress,
            memory,
            [](auto& address) {return fmt::format("0x{:0>8x}", address); },
            [](auto& pair) {return pair.first; }
        );
    }

    unsigned int AddressParameter::SelectedItem()
    { 
        return selectedAddress; 
    }

    void RegisterParameter::SelectWithUI(Registers& registers, Memory& memory)
    {
        if (registers.find(selectedRegister) == registers.end())
            selectedRegister = registers.begin()->first;

        Selector(
            "Register###" + std::to_string(reinterpret_cast<int>(this)),
            selectedRegister,
            registers,
            [](auto& reg) {return reg; },
            [](auto& pair) {return pair.first; }
        );
    }

    std::string RegisterParameter::SelectedItem() 
    { 
        return selectedRegister; 
    }
}