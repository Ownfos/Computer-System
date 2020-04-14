#include "Mesh.h"

namespace waffle
{
	template<typename T>
	Mesh<T>::Mesh(
		Context& context,
		std::vector<T>&& vertices,
		std::vector<unsigned int>&& indices,
		Topology topology
	)
		: context(context),
		vertices(std::move(vertices)),
		indices(std::move(indices)),
		topology(topology)
	{
		try
		{
			{
				D3D11_BUFFER_DESC desc{};
				desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				desc.ByteWidth = sizeof(T) * this->vertices.size();

				D3D11_SUBRESOURCE_DATA dataDesc{};
				dataDesc.pSysMem = &this->vertices[0];

				if (FAILED(context.Device()->CreateBuffer(&desc, &dataDesc, vertexBuffer.GetAddressOf())))
					throw std::exception("Failed to create vertex buffer");
			}
			{
				D3D11_BUFFER_DESC desc{};
				desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
				desc.ByteWidth = sizeof(int) * this->indices.size();

				D3D11_SUBRESOURCE_DATA dataDesc{};
				dataDesc.pSysMem = &this->indices[0];

				if (FAILED(context.Device()->CreateBuffer(&desc, &dataDesc, indexBuffer.GetAddressOf())))
					throw std::exception("Failed to create index buffer");
			}
		}
		catch (...)
		{
			std::throw_with_nested(std::exception("Mesh::Mesh()"));
		}
	}

	template<typename T>
	void Mesh<T>::Draw()
	{
		UINT stride = sizeof(T);
		UINT offset = 0U;
		context.DeviceContext()->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
		context.DeviceContext()->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		context.DeviceContext()->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(topology));
		context.DeviceContext()->DrawIndexed(indices.size(), 0, 0);
	}
}