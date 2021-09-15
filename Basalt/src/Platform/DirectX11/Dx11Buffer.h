#pragma once
#include <d3d11.h>
#include <wrl.h>

#include "Basalt/Renderer/Buffer.h"

namespace Basalt
{
	// TODO: Move to Dx11Shader once abstracted
	static DXGI_FORMAT ShaderDataTypeToDx11Type(const ShaderDataType type, const bool normalized)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return DXGI_FORMAT_R32_FLOAT;
			case ShaderDataType::Float2:	return DXGI_FORMAT_R32G32_FLOAT;
			case ShaderDataType::Float3:	return DXGI_FORMAT_R32G32B32_FLOAT;
			case ShaderDataType::Float4:	return DXGI_FORMAT_R32G32B32A32_FLOAT;
			case ShaderDataType::Mat3:		return DXGI_FORMAT_R32G32B32_FLOAT;
			case ShaderDataType::Mat4:		return DXGI_FORMAT_R32G32B32A32_FLOAT;
			case ShaderDataType::Char:		return normalized ? DXGI_FORMAT_R8_SNORM : DXGI_FORMAT_R8_SINT;
			case ShaderDataType::Char2:		return normalized ? DXGI_FORMAT_R8G8_SNORM : DXGI_FORMAT_R8G8_SINT;
			case ShaderDataType::Char4:		return normalized ? DXGI_FORMAT_R8G8B8A8_SNORM : DXGI_FORMAT_R8G8B8A8_SINT;
			case ShaderDataType::UChar:		return normalized ? DXGI_FORMAT_R8_UNORM : DXGI_FORMAT_R8_UINT;
			case ShaderDataType::UChar2:	return normalized ? DXGI_FORMAT_R8G8_UNORM : DXGI_FORMAT_R8G8_UINT;
			case ShaderDataType::UChar4:	return normalized ? DXGI_FORMAT_R8G8B8A8_UNORM : DXGI_FORMAT_R8G8B8A8_UINT;
			case ShaderDataType::Short:		return normalized ? DXGI_FORMAT_R16_SNORM : DXGI_FORMAT_R16_SINT;
			case ShaderDataType::Short2:	return normalized ? DXGI_FORMAT_R16G16_SNORM : DXGI_FORMAT_R16G16_SINT;
			case ShaderDataType::Short4:	return normalized ? DXGI_FORMAT_R16G16B16A16_SNORM : DXGI_FORMAT_R16G16B16A16_SINT;
			case ShaderDataType::UShort:	return normalized ? DXGI_FORMAT_R16_UNORM : DXGI_FORMAT_R16_UINT;
			case ShaderDataType::UShort2:	return normalized ? DXGI_FORMAT_R16G16_UNORM : DXGI_FORMAT_R16G16_UINT;
			case ShaderDataType::UShort4:	return normalized ? DXGI_FORMAT_R16G16B16A16_UNORM : DXGI_FORMAT_R16G16B16A16_UINT;
			case ShaderDataType::Int:		return DXGI_FORMAT_R32_SINT;
			case ShaderDataType::Int2:		return DXGI_FORMAT_R32G32_SINT;
			case ShaderDataType::Int3:		return DXGI_FORMAT_R32G32B32_SINT;
			case ShaderDataType::Int4:		return DXGI_FORMAT_R32G32B32A32_SINT;
			case ShaderDataType::UInt:		return DXGI_FORMAT_R32_UINT;
			case ShaderDataType::UInt2:		return DXGI_FORMAT_R32G32_UINT;
			case ShaderDataType::UInt3:		return DXGI_FORMAT_R32G32B32_UINT;
			case ShaderDataType::UInt4:		return DXGI_FORMAT_R32G32B32A32_UINT;
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

		void SetLayout(const BufferLayout& layout, std::unique_ptr<Shader>& shader) override;
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
