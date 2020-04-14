#ifndef SAMPLER_H
#define SAMPLER_H

#include "Context.h"

namespace waffle
{
    class Sampler
    {
    public:
        Sampler(Context& context, D3D11_TEXTURE_ADDRESS_MODE mode = D3D11_TEXTURE_ADDRESS_WRAP);

        void SetVS(UINT slot);
        void SetPS(UINT slot);

    private:
        Context& context;
        ComPtr<ID3D11SamplerState> sampler;
    };
}

#endif