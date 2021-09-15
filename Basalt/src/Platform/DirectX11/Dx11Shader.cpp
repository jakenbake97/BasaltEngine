#include "BEpch.h"
#include "Dx11Shader.h"

#include "Dx11Macros.h"

#include <d3dcompiler.h>
#include <utility>

namespace Basalt
{
	Dx11Shader::Dx11Shader(String vertexSource, String fragmentSource)
		: vertexPath(std::move(vertexSource)), pixelPath(std::move(fragmentSource))
	{
		const auto device = static_cast<ID3D11Device*>(Renderer::GetRenderContext().GetDevice());

		DX_INFO_CHECK(D3DReadFileToBlob(CString(vertexPath.CStr()), &vertexBlob));
		DX_INFO_CHECK(device->CreateVertexShader(vertexBlob->GetBufferPointer(), 
			vertexBlob->GetBufferSize(), nullptr, &vertexShader));

		DX_INFO_CHECK(D3DReadFileToBlob(CString(pixelPath.CStr()), &pixelBlob));
		DX_INFO_CHECK(device->CreatePixelShader(pixelBlob->GetBufferPointer(), 
			pixelBlob->GetBufferSize(), nullptr, &pixelShader));
	}

	void Dx11Shader::Bind() const
	{
		const auto context = static_cast<ID3D11DeviceContext*>(Renderer::GetRenderContext().GetDeviceContext());

		context->VSSetShader(vertexShader.Get(), nullptr, 0u);
		context->PSSetShader(pixelShader.Get(), nullptr, 0u);
	}

	void Dx11Shader::Unbind() const
	{
	}

	ID3DBlob* Dx11Shader::GetVertexBytecode() const
	{
		return vertexBlob.Get();
	}

	ID3DBlob* Dx11Shader::GetPixelBytecode() const
	{
		return pixelBlob.Get();
	}
}
