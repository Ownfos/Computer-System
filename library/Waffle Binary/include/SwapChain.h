#ifndef SWAP_CHAIN_H
#define SWAP_CHAIN_H

#include "Context.h"
#include "Window.h"
#include "ITextureResource.h"

namespace waffle
{
    class SwapChain : public ITextureResource
    {
    public:
        SwapChain(
            Context& context,
            const Window& window,
            MultiSampling sampleCount = MultiSampling::MSAA4x
        );
        ~SwapChain();

        void Present();
        void SetFullScreen(bool enable);
        void Resize(Rectangle size);

        virtual ID3D11Texture2D* Texture() override;
        virtual Rectangle Size() override;
        virtual MultiSampling SampleCount() override;

    private:
        Rectangle size;
        MultiSampling sampleCount;

        ComPtr<IDXGISwapChain> swapChain;
        ComPtr<ID3D11Texture2D> backBuffer;
    };
}
#endif