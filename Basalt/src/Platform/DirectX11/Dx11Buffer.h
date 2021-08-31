#pragma once
#include <d3d11.h>
#include <wrl.h>

#include "Basalt/Renderer/Buffer.h"

namespace Basalt
{
	class Dx11VertexBuffer : public VertexBuffer
	{
	public:
		Dx11VertexBuffer(const std::vector<struct Vertex>& vertices);
		~Dx11VertexBuffer() override;

		void Bind() override;
		void Unbind() override;

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
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
