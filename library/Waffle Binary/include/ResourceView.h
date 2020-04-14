#ifndef RESOURCE_VIEW_H
#define RESOURCE_VIEW_H

#include "Context.h"
#include "ITextureResource.h"

namespace waffle
{
	struct RenderTargetView
	{
		ComPtr<ID3D11RenderTargetView> view;

		RenderTargetView(Context& context, ITextureResource* resource);
	};

	struct DepthStencilView
	{
		ComPtr<ID3D11DepthStencilView> view;

		DepthStencilView(Context& context, ITextureResource* resource);
	};

	struct ShaderResourceView
	{
		ComPtr<ID3D11ShaderResourceView> view;

		ShaderResourceView(Context& context, ITextureResource* resource);
	};
}

#endif