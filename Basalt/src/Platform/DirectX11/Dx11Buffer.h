#pragma once
#include <d3d11.h>
#include <wrl.h>

#include "Basalt/Renderer/Buffer.h"

namespace Basalt
{
	static DXGI_FORMAT ShaderDataTypeToDx11Type(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return DXGI_FORMAT_R32_FLOAT;
			case ShaderDataType::Float2:	return DXGI_FORMAT_R32G32_FLOAT;
			case ShaderDataType::Float3:	return DXGI_FORMAT_R32G32B32_FLOAT;
			case ShaderDataType::Float4:	return DXGI_FORMAT_R32G32B32A32_FLOAT;
			case ShaderDataType::Mat3:		return DXGI_FORMAT_R32G32B32_FLOAT;
			case ShaderDataType::Mat4:		return DXGI_FORMAT_R32G32B32A32_FLOAT;
			case ShaderDataType::Int:		return DXGI_FORMAT_R32_SINT;
			case ShaderDataType::Int2:		return DXGI_FORMAT_R32G32_SINT;
			case ShaderDataType::Int3:		return DXGI_FORMAT_R32G32B32_SINT;
			case ShaderDataType::Int4:		return DXGI_FORMAT_R32G32B32A32_SINT;
			case ShaderDataType::Bool:		return DXGI_FORMAT_R32_UINT;
			default: BE_ERROR("ShaderDataType {0} is unknown", type); return DXGI_FORMAT_UNKNOWN;
		}
	}

	class Dx11VertexBuffer : public VertexBuffer
	{
	public:
		Dx11VertexBuffer(const std::vector<struct Vertex>& vertices);
		~Dx11VertexBuffer() override;

		void Bind() override;
		void Unbind() override;

		void SetLayout(const BufferLayout& layout) override;
		const BufferLayout& GetLayout() const override;

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
		BufferLayout bufLayout;
	};

	class Dx11IndexBuffer : public IndexBuffer
	{
	public:
		Dx11IndexBuffer(std::vector<uint32>& indices);
		~Dx11IndexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		uint32 GetCount() const override;

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
		uint32 count;
	};
}
