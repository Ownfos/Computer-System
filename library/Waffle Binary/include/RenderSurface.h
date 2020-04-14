#ifndef RENDER_SURFACE_H
#define RENDER_SURFACE_H

#include "Surface.h"
#include "ResourceView.h"

namespace waffle
{
    // A texture used for rendering or binding as shader resource
    // Use this as intermediate render target for post-processing effects
    class RenderSurface : public Surface
    {
    public:
        RenderSurface(Context& context, Rectangle size);

        void Clear(float r, float g, float b, float a, FLOAT depth = 1.0f, UINT8 stencil = 0);
        
        // Set as render target
        void SetRT();

        // Set as shader resource
        void SetVS(UINT slot);
        void SetPS(UINT slot);

    private:
        Context& context;
        Surface depthStencilBuffer;
        RenderTargetView rtv;
        DepthStencilView dsv;
        ShaderResourceView srv;
    };
}

#endif