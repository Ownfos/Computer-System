#ifndef IMGUI_HELPER_H
#define IMGUI_HELPER_H

#include "Context.h"
#include "RenderWindow.h"

#include "imgui.h"
#include "examples/imgui_impl_win32.h"
#include "examples/imgui_impl_dx11.h"

namespace waffle
{
	class ImGuiHelper
	{
	public:
		ImGuiHelper(Context& context, RenderWindow& window);

		void BeginFrame();
		void EndFrame();
	};
}

#endif