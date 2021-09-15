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

	private:
		String vertexPath;
		String pixelPath;
		Microsoft::WRL::ComPtr<ID3DBlob> vertexBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> pixelBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	};
}