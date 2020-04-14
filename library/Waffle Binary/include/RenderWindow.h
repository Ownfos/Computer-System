#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H

#include "Window.h"
#include "SwapChain.h"
#include "Surface.h"
#include "ResourceView.h"

namespace waffle
{
	// A window for rendering
	// Creates swapchain, depth stencil buffer, and resource views
	class RenderWindow : public Window
	{
	public:
		RenderWindow(
			Context& context,
			std::wstring title,
			Rectangle size,
			WindowType type = WindowType::Default,
			MultiSampling sampleCount = MultiSampling::MSAA4x
		);

		void Clear(float r, float g, float b, float a, FLOAT depth = 1.0f, UINT8 stencil = 0);
		void Set();

		void Present();

	private:
		Context& context;
		SwapChain swapChain;
		Surface depthStencilBuffer;
		RenderTargetView rtv;
		DepthStencilView dsv;
	};
}

#endif
