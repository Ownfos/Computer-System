#ifndef SURFACE_H
#define SURFACE_H

#include "Context.h"
#include "ITextureResource.h"

namespace waffle
{
	class Surface : public ITextureResource
	{
	public:
		// Depth stencil buffer for render target buffer
		Surface(
			Context& context,
			ITextureResource* renderTargetBuffer
		);

		// Buffer used as render target & shader resource
		Surface(
			Context& context,
			Rectangle size
		);

		virtual ID3D11Texture2D* Texture() override;
		virtual Rectangle Size() override;
		virtual MultiSampling SampleCount() override;

	protected:
		Rectangle size;
		MultiSampling sampleCount;
		ComPtr<ID3D11Texture2D> texture;

	private:
		Surface(
			Context& context,
			DXGI_FORMAT format,
			UINT bindFlags,
			Rectangle size,
			MultiSampling sampleCount
		);
	};
}

#endif
