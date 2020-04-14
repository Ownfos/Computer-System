#ifndef MESH_H
#define MESH_H

#include "Context.h"
#include <DirectXMath.h>
#include <vector>

namespace waffle
{
	struct Vertex
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texcoord;

		Vertex(DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 texcoord) : position(position), texcoord(texcoord) {}
	};

	enum class Topology
	{
		Triangle = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		Line = D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
		Point = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST
	};

	template<typename T>
	class Mesh
	{
	public:
		Mesh(
			Context& context,
			std::vector<T>&& vertices,
			std::vector<unsigned int>&& indices,
			Topology topology = Topology::Triangle
		);

		void Draw();

	private:
		Context& context;
		std::vector<T> vertices;
		std::vector<unsigned int> indices;
		Topology topology;
		ComPtr<ID3D11Buffer> vertexBuffer;
		ComPtr<ID3D11Buffer> indexBuffer;
	};
}

#include "Mesh.hpp"

#endif