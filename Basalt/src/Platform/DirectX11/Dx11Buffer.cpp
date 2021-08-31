#include "BEpch.h"
#include "Dx11Buffer.h"



#include "Dx11Context.h"
#include "Basalt/Renderer/Renderer.h"

namespace wrl = Microsoft::WRL;

namespace Basalt
{
	Dx11VertexBuffer::Dx11VertexBuffer(const std::vector<Vertex>& vertices)
	{
		D3D11_BUFFER_DESC bufDesc = {};
		bufDesc.Usage = D3D11_USAGE_DEFAULT;
		bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufDesc.CPUAccessFlags = 0u;
		bufDesc.MiscFlags = 0u;
		bufDesc.ByteWidth = (uint32)sizeof(Vertex) * (uint32)vertices.size();
		bufDesc.StructureByteStride = sizeof(Vertex);

		D3D11_SUBRESOURCE_DATA subresourceData = {};
		subresourceData.pSysMem = vertices.data();

		dynamic_cast<Dx11Context&>(Renderer::GetRenderContext()).GetDxDevice()->CreateBuffer(&bufDesc, &subresourceData, vertexBuffer.GetAddressOf());
	}

	Dx11VertexBuffer::~Dx11VertexBuffer()
	{
		// TODO: Delete the vertex buffer
	}

	void Dx11VertexBuffer::Bind()
	{
		const uint32 stride = sizeof(Vertex);
		const uint32 offset = 0u;
		dynamic_cast<Dx11Context&>(Renderer::GetRenderContext()).GetDxDeviceContext()->IASetVertexBuffers(0u, 1u, vertexBuffer.GetAddressOf(), &stride, &offset);
	}

	void Dx11VertexBuffer::Unbind()
	{
	}

	Dx11IndexBuffer::Dx11IndexBuffer(std::vector<uint32>& indices)
		: count((uint32)indices.size())
	{
	}

	Dx11IndexBuffer::~Dx11IndexBuffer()
	{
		// TODO: Delete the Index buffer
		
	}

	void Dx11IndexBuffer::Bind() const
	{
		
	}

	void Dx11IndexBuffer::Unbind() const
	{
	}

	uint32 Dx11IndexBuffer::GetCount() const
	{
		return count;
	}
}
