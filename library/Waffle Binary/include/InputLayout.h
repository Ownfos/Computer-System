#ifndef INPUT_LAYOUT_H
#define INPUT_LAYOUT_H

#include "Context.h"
#include "ShaderBlob.h"
#include "InputElement.h"
#include <vector>

namespace waffle
{
    class InputLayout
    {
    public:
        InputLayout(
            Context& context, 
            ShaderBlob& blob,
            std::vector<InputElement> elements
        );

        ID3D11InputLayout* Get();

    private:
        std::vector<InputElement> elements;
        ComPtr<ID3D11InputLayout> layout;
    };
}

#endif