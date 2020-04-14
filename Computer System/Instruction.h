#pragma once

#include "TypeDefinition.h"
#include "Visitor.h"
#include "Parameters.h"
#include "imgui.h"
#include "fmt/format.h"
#include <optional>
#include <variant>

#define PARAMETER(T) T, T::Type
#define CLASSNAME(T) virtual std::string ClassName() const override {return #T; }
#define UNARYINSTRUCTIONCLASS(T) CLASSNAME(T) using UnaryInstruction::UnaryInstruction;
#define BINARYINSTRUCTIONCLASS(T) CLASSNAME(T) using BinaryInstruction::BinaryInstruction;

namespace ownfos
{
    // Base class for all executable instructions
    class Instruction
    {
    public:
        virtual std::string ClassName() const = 0;
        virtual std::string Format() const = 0;
        virtual std::optional<std::shared_ptr<Instruction>> ConstructWithUI(Registers& registers, Memory& memory) = 0;
        virtual void Execute(Registers& registers, Memory& memory) = 0;
    };

    // Utility template class for creating custom instruction with two operands.
    // Derived class can access operands through protected member variable "operand".
    //
    // Use macros PARAMETER() to pass Parameter and ParameterType at once,
    // and UNARYINSTRUCTIONCLASS() to generate appropriate constructor.
    //
    // Example (instruction using single address as operand):
    // class MyInstruction : public UnaryInstruction<PARAMETER(AddressParameter), MyInstruction>
    // {
    //      UNARYINSRUCTIONCLASS(MyInstruction)
    //
    //      virtual std::string Format() const override { /* Implement your logic */ }
    //      virtual void Execute(...) { /* Implement your logic */ }
    // }
    template<typename Parameter, typename ParameterType, typename DerivedClass>
    class UnaryInstruction : public Instruction
    {
    public:
        UnaryInstruction(ParameterType operand)
            : operand(operand)
        {}

        virtual std::optional<std::shared_ptr<Instruction>> ConstructWithUI(Registers& registers, Memory& memory) override
        {
            parameter.SelectWithUI(registers, memory);
            if (ImGui::Button(("Enter###" + std::to_string(reinterpret_cast<int>(this))).c_str()))
                return std::make_shared<DerivedClass>(parameter.SelectedItem());
            return {};
        }

    protected:
        ParameterType operand;

    private:
        Parameter parameter;
    };

    // Utility template class for creating custom instruction with two operands.
    // Derived class can access operands through protected member variable "operand1" and "operand2".
    //
    // Use macros PARAMETER() to pass Parameter and ParameterType at once,
    // and BINARYINSTRUCTIONCLASS() to generate appropriate constructor.
    //
    // Example (instruction using single address and single register name as operands):
    // class MyInstruction : public BinaryInstruction<PARAMETER(AddressParameter), PARAMETER(RegisterParameter), MyInstruction>
    // {
    //      BINARYINSRUCTIONCLASS(MyInstruction)
    //
    //      virtual std::string Format() const override { /* Implement your logic */ }
    //      virtual void Execute(...) { /* Implement your logic */ }
    // }
    template<typename Parameter1, typename Parameter1Type, typename Parameter2, typename Parameter2Type, typename DerivedClass>
    class BinaryInstruction : public Instruction
    {
    public:
        BinaryInstruction(Parameter1Type operand1, Parameter2Type operand2)
            : operand1(operand1), operand2(operand2)
        {}

        virtual std::optional<std::shared_ptr<Instruction>> ConstructWithUI(Registers& registers, Memory& memory) override
        {
            parameter1.SelectWithUI(registers, memory);
            parameter2.SelectWithUI(registers, memory);
            if (ImGui::Button(("Enter###" + std::to_string(reinterpret_cast<int>(this))).c_str()))
                return std::make_shared<DerivedClass>(parameter1.SelectedItem(), parameter2.SelectedItem());
            return {};
        }

    protected:
        Parameter1Type operand1;
        Parameter2Type operand2;

    private:
        Parameter1 parameter1;
        Parameter2 parameter2;
    };
}