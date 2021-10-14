#pragma once
#include <d3d11.h>
#include <wrl.h>

#include "Basalt/Renderer/Buffer.h"

namespace Basalt
{
	class Dx11VertexBuffer : public VertexBuffer
	{
	public:
		template<typename T>
		Dx11VertexBuffer(const std::vector<T>& vertices, std::unique_ptr<Shader>& shader, const BufferLayout& layout)
		{
			Dx11VertexBuffer::SetLayout(layout, shader);
			uint32 vertSize = sizeof(T);

			if (vertSize != layout.GetStride())
			{
				BE_ERROR("The vertex size: {0} does not match layout size: {1}", vertSize, layout.GetStride());
			}

			std::vector<char> byteBuffer(vertices.size() * vertSize);
			for (int i = 0; i < vertices.size(); i++)
			{
				char* currentElement = &byteBuffer[i * vertSize];
				*reinterpret_cast<T*>(currentElement) = vertices[i];
			}

			CreateAndBindBuffer(byteBuffer);
		}
		~Dx11VertexBuffer() override;

		void Bind() override;
		void Unbind() override;

		void SetLayout(const BufferLayout& layout, std::unique_ptr<Shader>& shader) override;
		void SetData(const std::vector<char>& vertices);
		const BufferLayout& GetLayout() const override;
		void CreateAndBindBuffer(const std::vector<char>& vertexData);

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
