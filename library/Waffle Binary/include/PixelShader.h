#ifndef PIXEL_SHADER_H
#define PIXEL_SHADER_H

#include "Context.h"
#include "ShaderBlob.h"

namespace waffle
{
    class PixelShader
    {
    public:
        PixelShader(Context& context, ShaderBlob&& blob);

        void Set();

    private:
        Context& context;
        ShaderBlob blob;
        ComPtr<ID3D11PixelShader> shader;
    };
}

#endif