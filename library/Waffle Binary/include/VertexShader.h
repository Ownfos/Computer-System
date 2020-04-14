#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H

#include "InputLayout.h"

namespace waffle
{
    class VertexShader
    {
    public:
        VertexShader(
            Context& context,
            ShaderBlob&& blob,
            std::vector<InputElement> elements
        );

        void Set();

    private:
        Context& context;
        ShaderBlob blob;
        InputLayout layout;
        ComPtr<ID3D11VertexShader> shader;
    };
}

#endif