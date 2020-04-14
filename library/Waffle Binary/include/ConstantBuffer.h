#ifndef CONSTANT_BUFFER_H
#define CONSTANT_BUFFER_H

#include "Context.h"

namespace waffle
{
	template<typename T>
	class ConstantBuffer
	{
	public:
		ConstantBuffer(Context& context, const T& data);

		void Update(const T& data);

		void SetVS(UINT slot);
		void SetPS(UINT slot);

	private:
		Context& context;
		T data;
		ComPtr<ID3D11Buffer> buffer;
	};
}

#include "ConstantBuffer.hpp"

#endif