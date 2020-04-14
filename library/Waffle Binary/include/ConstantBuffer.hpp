#include "ConstantBuffer.h"

#include <exception>

namespace waffle
{

    template<typename T>
	ConstantBuffer<T>::ConstantBuffer(Context& context, const T& data)
		: context(context), data(data)
	{
		try
		{
			D3D11_BUFFER_DESC desc{};
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.ByteWidth = sizeof(T);

			D3D11_SUBRESOURCE_DATA subresourceDesc{};
			subresourceDesc.pSysMem = &this->data;

			if (FAILED(context.Device()->CreateBuffer(&desc, &subresourceDesc, buffer.GetAddressOf())))
				throw std::exception("Failed to create constant buffer");
		}
		catch (...)
		{
			std::throw_with_nested(std::exception("ConstantBuffer::ConstantBuffer()"));
		}
	}

	template<typename T>
	void ConstantBuffer<T>::Update(const T& data)
	{
		this->data = data;
		context.DeviceContext()->UpdateSubresource(
			buffer.Get(),
			0,
			nullptr,
			&this->data,
			0,
			0
		);
	}

	template<typename T>
	void ConstantBuffer<T>::SetVS(UINT slot)
	{
		context.DeviceContext()->VSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
	}

	template<typename T>
	void ConstantBuffer<T>::SetPS(UINT slot)
	{
		context.DeviceContext()->PSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
	}
}