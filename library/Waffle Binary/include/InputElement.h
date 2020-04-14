#ifndef INPUT_ELEMENT_H
#define INPUT_ELEMENT_H

#include <d3d11.h>
#include <string>

namespace waffle
{
    enum class InputFormat
    {
        Float2,
        Float3,
        Float4,
    };

    class InputElement
    {
    public:
        InputElement(std::string semanticName, InputFormat format);

        const char* Name();
        DXGI_FORMAT Format();
        UINT Size();

    private:
        std::string semanticName;
        DXGI_FORMAT format;
        UINT bytesPerPixel;
    };
}

#endif