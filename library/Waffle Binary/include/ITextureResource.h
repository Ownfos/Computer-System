#ifndef I_TEXTURE_RESOURCE_H
#define I_TEXTURE_RESOURCE_H

#include "Rectangle.h"

class ID3D11Texture2D;

namespace waffle
{
    enum class MultiSampling
    {
        None = 1,
        MSAA4x = 4,
        MSAA8x = 8,
    };

    class ITextureResource
    {
    public:
        virtual ~ITextureResource() = default;

        virtual ID3D11Texture2D* Texture() = 0;
        virtual Rectangle Size() = 0;
        virtual MultiSampling SampleCount() = 0;
    };
}

#endif