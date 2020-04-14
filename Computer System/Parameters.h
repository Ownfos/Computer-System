#pragma once

#include "TypeDefinition.h"

// These Parameter classes are used as template argument in UnaryInstruction and BinaryInstruction
// to automatically generate required member variables for each operand and
// function for showing parameter input UI.
namespace ownfos
{
    // Used to recieve single integer input
    class ValueParameter
    {
    public:
        using Type = int;

        void SelectWithUI(Registers& registers, Memory& memory);

        unsigned int SelectedItem();

    private:
        int value = 0;
    };

    // Used to choose an address from existing memory addresses
    class AddressParameter
    {
    public:
        using Type = unsigned int;

        void SelectWithUI(Registers& registers, Memory& memory);

        unsigned int SelectedItem();

    private:
        unsigned int selectedAddress = 0;
    };

    // Used to choose a register name from existing registers
    class RegisterParameter
    {
    public:
        using Type = std::string;

        void SelectWithUI(Registers& registers, Memory& memory);

        std::string SelectedItem();

    private:
        std::string selectedRegister = "";
    };
}