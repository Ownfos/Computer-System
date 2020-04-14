#include "Instruction.h"
#include "Selector.h"
#include "Waffle.h"
#include "imgui.h"
#include "fmt/format.h"
#include <memory>
#include <set>

namespace ownfos
{
    class Move : public BinaryInstruction<PARAMETER(RegisterParameter), PARAMETER(RegisterParameter), Move>
    {
    public:
        BINARYINSTRUCTIONCLASS(Move)

        virtual std::string Format() const override { return fmt::format("Move {}, {}", operand1, operand2); }
        virtual void Execute(Registers& registers, Memory&)
        {
            registers[operand1] = registers[operand2];
        }
    };

    class Add : public BinaryInstruction<PARAMETER(RegisterParameter), PARAMETER(RegisterParameter), Add>
    {
    public:
        BINARYINSTRUCTIONCLASS(Add)

        virtual std::string Format() const override { return fmt::format("Add {}, {}", operand1, operand2); }
        virtual void Execute(Registers& registers, Memory&)
        {
            registers[operand1] = std::get<0>(registers[operand1]) + std::get<0>(registers[operand2]);
        }
    };

    class Jump : public UnaryInstruction<PARAMETER(AddressParameter), Jump>
    {
    public:
        UNARYINSTRUCTIONCLASS(Jump)

        virtual std::string Format() const override { return fmt::format("Jump 0x{:0>8x}", operand); }
        virtual void Execute(Registers& registers, Memory& memory)
        {
            registers["PC"] = operand;
        }
    };

    class Load : public BinaryInstruction<PARAMETER(RegisterParameter), PARAMETER(AddressParameter), Load>
    {
    public:
        BINARYINSTRUCTIONCLASS(Load)

        virtual std::string Format() const { return fmt::format("Load {}, 0x{:0>8x}", operand1, operand2); }
        virtual void Execute(Registers& registers, Memory& memory)
        {
            registers["MAR"] = operand2;
            registers["MBR"] = registers[operand1] = memory[operand2];
        }
    };

    class Store : public BinaryInstruction<PARAMETER(AddressParameter), PARAMETER(RegisterParameter), Store>
    {
    public:
        BINARYINSTRUCTIONCLASS(Store)

        virtual std::string Format() const { return fmt::format("Store 0x{:0>8x}, {}", operand1, operand2); }
        virtual void Execute(Registers& registers, Memory& memory)
        {
            registers["MAR"] = operand1;
            registers["MBR"] = memory[operand1] = registers[operand2];
        }
    };
}


int main()
{
    auto registers = ownfos::Registers{
        {"R1", 0}, 
        {"R2", 1}, 
        {"PC", 0}, 
        {"MAR", 0}, 
        {"MBR", 0}
    };

    auto memory = ownfos::Memory{ 
        {0, std::make_shared<ownfos::Add>("R1", "R2")}, 
        {1, std::make_shared<ownfos::Store>(100, "R1")}, 
        {2, std::make_shared<ownfos::Jump>(0)},
        {100, 0}
    };

    // These prototypes will be used by dataMapUI (the lambda right below this), 
    // whuich iterates over this set to show constructable instructions in GUI.
    // If you wish to use your custom instruction with GUI, add a prototype here.
    auto instructionPrototypes = std::set<std::shared_ptr<ownfos::Instruction>>{
        std::make_shared<ownfos::Move>("", ""),
        std::make_shared<ownfos::Add>("", ""),
        std::make_shared<ownfos::Load>("", 0),
        std::make_shared<ownfos::Store>(0, ""),
        std::make_shared<ownfos::Jump>(0),
    };

    // This lambda will show GUI for any map with value type
    // as std::variant<int, std::shared_ptr<Instruction>>,
    // which includes memory and register map.
    //
    // keyFormatter: Lambda which transforms data to a formatted string.
    // highlightKey: A key which will be displayed in yellow color.
    //               Used to mark next instruction to be executed.
    auto dataMapUI = [&](auto& map, auto keyFormatter, auto highlightKey) {
        for (auto& [key, data] : map)
        {
            // Show content with distinct color (highlight: yellow, hovered: white, elsewhere: gray)
            auto formattedData = std::visit(ownfos::Visitor{
                [](int& i) {return fmt::format("0x{:0>8x} ({})", static_cast<unsigned int>(i), i); },
                [](std::shared_ptr<ownfos::Instruction>& instruction) {return instruction->Format(); }
            }, data);
            auto content = fmt::format("{} : {}", keyFormatter(key), formattedData);
            static auto hoveredKey = key;
            if (key == highlightKey)
            {
                ImGui::TextColored(ImVec4(1, 1, 0, 1), content.c_str());
            }
            else if (key == hoveredKey)
            {
                ImGui::Text(content.c_str());
                // If nothing is hovered, only color the highlighted item.
                // When hoveredKey is same as highlightKey,
                // only the first if statement will execute.
                if (!ImGui::IsItemHovered())
                    hoveredKey = highlightKey;
            }
            else
            {
                ImGui::TextDisabled(content.c_str());
                if (ImGui::IsItemHovered())
                    hoveredKey = key;
            }

            // Popup for constructing memory content (either a value or an instruction)
            if (ImGui::BeginPopupContextItem(keyFormatter(key).c_str()))
            {
                // Select whether you want to create a value or an instruction
                static std::string selectedDataType = "Value";
                ownfos::Selector(
                    "Data Type",
                    selectedDataType,
                    std::set<std::string>{"Value", "Instruction"},
                    [](auto& type) {return type; },
                    [](auto& type) {return type; }
                );
                ImGui::Separator();

                if (selectedDataType == "Value")
                {
                    // Recieve a value
                    static int value = 0;
                    ImGui::InputInt("Value", &value);
                    if (ImGui::Button("Enter"))
                    {
                        map[key] = value;
                        ImGui::CloseCurrentPopup();
                    }
                }
                else
                {
                    // Select which instruction (from the prototypes) you wish to create
                    static std::shared_ptr<ownfos::Instruction> selectedInstructionType = *instructionPrototypes.begin();
                    ownfos::Selector(
                        "Instruction Type",
                        selectedInstructionType,
                        instructionPrototypes,
                        [](auto& instruction) {return instruction->ClassName(); },
                        [](auto& instruction) {return instruction; }
                    );

                    // Try recieving parameter by UI and assign it to map when button is pushed
                    if (auto instruction = selectedInstructionType->ConstructWithUI(registers, memory); instruction.has_value())
                    {
                        map[key] = instruction.value();
                        ImGui::CloseCurrentPopup();
                    }
                }

                ImGui::EndPopup();
            }
        }
    };

    try
    {
        auto context = waffle::Context();
        auto window = waffle::RenderWindow(context, L"Computer System", { 1000, 600 }, waffle::WindowType::DisableResizing);
        auto ui = waffle::ImGuiHelper(context, window);

        return waffle::Window::MessageLoop([&] {
            window.input.UpdateFrameState();
            if (window.input.RawState(waffle::KeyCode::Esc))
            {
                waffle::Window::Quit();
            }

            static float backgroundColor[3] = { 1.0f, 1.0f, 1.0f };
            window.Clear(
                backgroundColor[0],
                backgroundColor[1], 
                backgroundColor[2],
                1.0f
            );
            window.Set();
            ui.BeginFrame();
            {
                ImGui::Begin("Help", 0, ImGuiWindowFlags_AlwaysAutoResize);
                {
                    ImGui::SliderFloat3("Background Color", backgroundColor, 0.0f, 1.0f);
                    ImGui::Separator();
                    if (ImGui::TreeNodeEx("Program Usage", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed))
                    {
                        ImGui::Text("- Press space to execute next instruction");
                        ImGui::Text("- Press escape to quit");
                        ImGui::Text("- Right click on register or memory to update its content");
                        ImGui::Text("- Current instruction is highlighted in yellow color");
                        ImGui::TreePop();
                    }
                    if (ImGui::TreeNodeEx("Program Info", ImGuiTreeNodeFlags_Framed))
                    {
                        ImGui::Text("Used tools");
                        ImGui::Text("- Waffle (https://github.com/Ownfos/Waffle)");
                        ImGui::Text("- ImGui (https://github.com/ocornut/imgui)");
                        ImGui::Text("- Microsoft Visual Studio Community 2019 version 16.5.3");
                        ImGui::TreePop();
                    }
                }
                ImGui::End();

                ImGui::Begin("Computer", 0, ImGuiWindowFlags_AlwaysAutoResize);
                {
                    // Fetch next instruction
                    auto instructionAddress = static_cast<unsigned int>(std::get<0>(registers["PC"]));
                    auto instruction = std::get<1>(memory[instructionAddress]);
                    
                    // Execute next instruction
                    if (window.input.FrameState(waffle::KeyCode::Space) == waffle::InputState::PressedNow)
                    {
                        registers["MAR"] = instructionAddress;
                        registers["MBR"] = instruction;
                        instruction->Execute(registers, memory);
                        if (instruction->ClassName() != "Jump")
                        {
                            registers["PC"] = instructionAddress + 1;
                        }
                    }

                    // Show register content
                    if (ImGui::TreeNodeEx("Registers", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed))
                    {
                        dataMapUI(registers, [](auto& key) {return key; }, "");
                        ImGui::Separator();

                        // UI for creating new register.
                        // Show if there was any exception from input in red color.
                        static std::string lastExceptionMessage = "";
                        if (lastExceptionMessage != "")
                        {
                            ImGui::TextColored(ImVec4(1, 0, 0, 1), lastExceptionMessage.c_str());
                        }

                        static char newRegisterName[128] = "";
                        ImGui::InputTextWithHint("###Register Name", "new register name", newRegisterName, IM_ARRAYSIZE(newRegisterName));
                        ImGui::SameLine();
                        if (ImGui::Button("Create Register"))
                        {
                            try
                            {
                                if (std::string(newRegisterName).length() == 0)
                                    throw std::exception("Register name shouldn't be empty");

                                registers.insert({ newRegisterName, 0 });
                                lastExceptionMessage = "";
                                newRegisterName[0] = '\0';
                            }
                            catch (std::exception& exception)
                            {
                                lastExceptionMessage = fmt::format("Invalid Name! ({})", exception.what());
                            }
                        }
                        ImGui::TreePop();
                    }

                    // Show memory content
                    if (ImGui::TreeNodeEx("Memory", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed))
                    {
                        dataMapUI(memory, [](auto& key) {return fmt::format("0x{:0>8x}", key); }, instructionAddress);
                        ImGui::Separator(); 

                        // UI for allocating new memory address.
                        // Show if there was any exception from input in red color.
                        static std::string lastExceptionMessage = "";
                        if (lastExceptionMessage != "")
                        {
                            ImGui::TextColored(ImVec4(1, 0, 0, 1), lastExceptionMessage.c_str());
                        }

                        static char newAddress[128] = "";
                        ImGui::InputTextWithHint("###Address", "123ff", &newAddress[0], IM_ARRAYSIZE(newAddress));
                        ImGui::SameLine();
                        if (ImGui::Button("Allocate"))
                        {
                            try
                            {
                                auto castedAddress = std::stoi(newAddress, 0, 16);
                                if (memory.find(castedAddress) != memory.end())
                                    throw std::exception("This address is already allocated");

                                memory[castedAddress] = 0;
                                lastExceptionMessage = "";
                                newAddress[0] = '\0';
                            }
                            catch (std::exception& exception)
                            {
                                lastExceptionMessage = fmt::format("Invalid Address! ({})", exception.what());
                            }
                        }
                        ImGui::TreePop();
                    }
                }
                ImGui::End();

            }
            ui.EndFrame();
            window.Present();
        });
    }
    catch (std::exception& exception)
    {
        waffle::PrintNestedException(exception);
        return -1;
    }
}