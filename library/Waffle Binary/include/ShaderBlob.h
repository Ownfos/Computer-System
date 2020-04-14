#ifndef SHADER_BLOB_H
#define SHADER_BLOB_H

#include "Utility.h"
#include <d3dcompiler.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

namespace waffle
{
    class ShaderBlob
    {
    public:
        ShaderBlob(std::wstring relativePath);

        const void* Pointer();
        SIZE_T Size();

    private:
        ComPtr<ID3DBlob> blob;
    };
}

#endif