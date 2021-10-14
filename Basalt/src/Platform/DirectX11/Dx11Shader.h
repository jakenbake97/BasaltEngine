#pragma once

#include "Basalt/Renderer/Shader.h"

#include <d3d11.h>
#include <d3dcommon.h>
#include <wrl/client.h>

namespace Basalt
{
	class Dx11Shader : public Shader
	{
	public:
		Dx11Shader(String vertexSource, String fragmentSource);
		~Dx11Shader() override = default;

		void Bind() const override;
		void Unbind() const override;

		ID3DBlob* GetVertexBytecode() const;
		ID3DBlob* GetPixelBytecode() const;

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

	private:
		String vertexPath;
		String pixelPath;
		Microsoft::WRL::ComPtr<ID3DBlob> vertexBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> pixelBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	};
}