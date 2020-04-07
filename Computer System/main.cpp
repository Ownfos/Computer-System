#include "InstructionExecutor.h"
#include "Memory.h"
#include "Move.h"
#include "Jump.h"
#include "Load.h"
#include "Store.h"

#include "Waffle.h"
#include "fmt/format.h"

#include <iostream>
#include <sstream>

using namespace ownfos;
using namespace waffle;

int main()
{
	try
	{
		auto memory = Memory();
		auto cpu = InstructionExecutor(memory);

		// Memory block #1
		memory[0x0] = Move(1, 2);
		memory[0x1] = Jump(0x103);

		// Memory block #2
		memory[0x100] = 12345678;
		memory[0x101] = 7777;
		memory[0x103] = Store(0x100, 0);
		memory[0x104] = Load(2, 0x101);
		memory[0x105] = Move(0, 2);
		memory[0x106] = Jump(0x0);

		auto context = Context();
		auto window = RenderWindow(context, L"title", { 1000, 600 });
		auto ui = ImGuiHelper(context, window);

		return Window::MessageLoop([&]
			{
				// Handle input
				if (window.input.RawState(KeyCode::Esc))
					Window::Quit();

				// Draw anything you want
				static float rgb[3]{ 0.41f, 0.48f, 0.57f };
				window.Clear(rgb[0], rgb[1], rgb[2], 1);
				window.Set();
				{
					ui.BeginFrame();
					{
						ImGui::Begin("Background color");
						ImGui::SliderFloat3("RGB color", rgb, 0.0f, 1.0f);
						ImGui::End();
						memory.GUI();
						cpu.GUI();
					}
					ui.EndFrame();
				}
				window.Present();
			});
	}
	catch (const std::exception& e)
	{
		PrintNestedException(e);
		return -1;
	}
}