#ifndef CONTEXT_H
#define CONTEXT_H

#include <d3d11.h>
#include <dxgi1_2.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

namespace waffle
{
    // Handles creation of d3d11 factory, device, and immediate context
    // Debug mode will generate extra debug messages automatically
    class Context
    {
    public:
        Context();

        IDXGIFactory1* Factory();
        ID3D11Device* Device();
        ID3D11DeviceContext* DeviceContext();

        void UnbindVSResource(UINT slot);
        void UnbindPSResource(UINT slot);

    private:
        ComPtr<IDXGIFactory1> factory;
        ComPtr<ID3D11Device> device;
        ComPtr<ID3D11DeviceContext> deviceContext;
#ifdef _DEBUG
        ComPtr<ID3D11Debug> debug;
#endif
    };
}

#endif