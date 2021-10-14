#include "BEpch.h"
#include "Dx11Buffer.h"
#include "Dx11Context.h"
#include "Dx11Macros.h"
#include "Dx11Shader.h"
#include "Basalt/Renderer/Renderer.h"

namespace wrl = Microsoft::WRL;

namespace Basalt
{
	/******************************
	 ***********Vertex Buffer******
	 ******************************/

	Dx11VertexBuffer::~Dx11VertexBuffer()= default;

	void Dx11VertexBuffer::Bind()
	{
		const uint32 stride = bufLayout.GetStride();
		constexpr uint32 offset = 0u;
		static_cast<ID3D11DeviceContext*>(Renderer::GetRenderContext().GetDeviceContext())->IASetVertexBuffers(0u, 1u, vertexBuffer.GetAddressOf(), &stride, &offset);
	}

	void Dx11VertexBuffer::Unbind()
	{
		static_cast<ID3D11DeviceContext*>(Renderer::GetRenderContext().GetDeviceContext())->IASetVertexBuffers(0u, 0u, nullptr, nullptr, nullptr);
	}

	void Dx11VertexBuffer::SetLayout(const BufferLayout& layout, std::unique_ptr<Shader>& shader)
	{
		bufLayout = layout;
		auto blob = dynamic_cast<Dx11Shader*>(shader.get())->GetVertexBytecode();
		wrl::ComPtr<ID3D11InputLayout> inputLayout;
		std::vector<D3D11_INPUT_ELEMENT_DESC> inElementDesc{};
		for (const auto& element : layout)
		{
			inElementDesc.push_back(
				{element.name.CStr(), 0u,
					Dx11Shader::ShaderDataTypeToDx11Type(element.type, element.normalized), 0u, element.offset, D3D11_INPUT_PER_VERTEX_DATA, 0u
				});
		}

		DX_INFO_CHECK(static_cast<ID3D11Device*>(Renderer::GetRenderContext().GetDevice())->CreateInputLayout(inElementDesc.data(), (uint32)inElementDesc.size(), blob->GetBufferPointer(), blob->GetBufferSize(), inputLayout.GetAddressOf()));

		static_cast<ID3D11DeviceContext*>(Renderer::GetRenderContext().GetDeviceContext())->IASetInputLayout(inputLayout.Get());
	}

	const BufferLayout& Dx11VertexBuffer::GetLayout() const
	{
		return bufLayout;
	}

	void Dx11VertexBuffer::CreateAndBindBuffer(const std::vector<char>& vertexData)
	{
		D3D11_BUFFER_DESC bufDesc = {};
		bufDesc.Usage = D3D11_USAGE_DEFAULT;
		bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufDesc.CPUAccessFlags = 0u;
		bufDesc.MiscFlags = 0u;
		bufDesc.ByteWidth = (uint32)vertexData.size();
		bufDesc.StructureByteStride = bufLayout.GetStride();

		D3D11_SUBRESOURCE_DATA subresourceData = {};
		subresourceData.pSysMem = vertexData.data();

		DX_INFO_CHECK(static_cast<ID3D11Device*>(Renderer::GetRenderContext().GetDevice())->CreateBuffer(&bufDesc, &subresourceData, vertexBuffer.GetAddressOf()));
	}

	/******************************
	 ***********Index Buffer*******
	 ******************************/

	Dx11IndexBuffer::Dx11IndexBuffer(std::vector<uint32>& indices)
		: count((uint32)indices.size())
	{
		D3D11_BUFFER_DESC indBufDesc = {};
		indBufDesc.Usage = D3D11_USAGE_DEFAULT;
		indBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indBufDesc.CPUAccessFlags = 0u;
		indBufDesc.MiscFlags = 0u;
		indBufDesc.ByteWidth = (uint32)sizeof(uint32) * (uint32)indices.size();
		indBufDesc.StructureByteStride = sizeof(uint32);

		D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
		indexSubresourceData.pSysMem = indices.data();

		DX_INFO_CHECK(static_cast<ID3D11Device*>(Renderer::GetRenderContext().GetDevice())->CreateBuffer(&indBufDesc, &indexSubresourceData, indexBuffer.GetAddressOf()));

		Dx11IndexBuffer::Bind();
	}

	Dx11IndexBuffer::~Dx11IndexBuffer() = default;

	void Dx11IndexBuffer::Bind() const
	{
		static_cast<ID3D11DeviceContext*>(Renderer::GetRenderContext().GetDeviceContext())->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
	}

	void Dx11IndexBuffer::Unbind() const
	{
		static_cast<ID3D11DeviceContext*>(Renderer::GetRenderContext().GetDeviceContext())->IASetIndexBuffer(nullptr, DXGI_FORMAT_R32_UINT, 0u);
	}

	uint32 Dx11IndexBuffer::GetCount() const
	{
		return count;
	}
}
