#pragma once
#include <d3d11.h>
#include <wrl.h>

#include "Dx11Macros.h"
#include "Basalt/Renderer/Buffer.h"

namespace Basalt
{
	class Dx11VertexBuffer : public VertexBuffer
	{
	public:
		template <typename T>
		Dx11VertexBuffer(const std::vector<T>& vertices, const std::unique_ptr<Shader>& shader,
		                 const BufferLayout& layout)
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
				char* currentElement = &byteBuffer[vertSize * i];
				*reinterpret_cast<T*>(currentElement) = vertices[i];
			}

			CreateAndBindBuffer(byteBuffer);
		}

		~Dx11VertexBuffer() override;

		void Bind() override;
		void Unbind() override;

		void SetLayout(const BufferLayout& layout, const std::unique_ptr<Shader>& shader) override;
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

	template <typename T>
	class Dx11ConstantBuffer : public ConstantBuffer<T>
	{
	public:
		Dx11ConstantBuffer(const Dx11ConstantBuffer& other) = delete;
		Dx11ConstantBuffer(Dx11ConstantBuffer&& other) noexcept = delete;
		Dx11ConstantBuffer& operator=(const Dx11ConstantBuffer& other) = delete;
		Dx11ConstantBuffer& operator=(Dx11ConstantBuffer&& other) noexcept = delete;

		Dx11ConstantBuffer()
		{
			D3D11_BUFFER_DESC bufDesc = {};
			bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bufDesc.Usage = D3D11_USAGE_DYNAMIC;
			bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bufDesc.MiscFlags = 0u;
			bufDesc.ByteWidth = sizeof(T);
			bufDesc.StructureByteStride = 0u;

			DX_INFO_CHECK(static_cast<ID3D11Device*>(Renderer::GetRenderContext().GetDevice())->CreateBuffer(&bufDesc, nullptr, &constantBuffer));
		}

		Dx11ConstantBuffer(T data)
		{
			D3D11_BUFFER_DESC bufDesc = {};
			bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bufDesc.Usage = D3D11_USAGE_DYNAMIC;
			bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bufDesc.MiscFlags = 0u;
			bufDesc.ByteWidth = sizeof(T);
			bufDesc.StructureByteStride = 0u;

			D3D11_SUBRESOURCE_DATA subresourceData = {};
			subresourceData.pSysMem = &data;

			DX_INFO_CHECK(static_cast<ID3D11Device*>(Renderer::GetRenderContext().GetDevice())->CreateBuffer(&bufDesc, &subresourceData, &constantBuffer));
		}

		~Dx11ConstantBuffer() override = default;

		void Bind(const ShaderType type) const override
		{
			switch (type)
			{
				case ShaderType::Vertex: 
					static_cast<ID3D11DeviceContext*>(Renderer::GetRenderContext().GetDeviceContext())->VSSetConstantBuffers(0u, 1u, constantBuffer.GetAddressOf());
					return;
				case ShaderType::Fragment: 
					static_cast<ID3D11DeviceContext*>(Renderer::GetRenderContext().GetDeviceContext())->PSSetConstantBuffers(0u, 1u, constantBuffer.GetAddressOf());
					return;
				default: BE_ERROR("Constant Buffer cannot be bound to Shader Type {0}", type);
			}
		}
		void UpdateData(const T& data) override
		{
			D3D11_MAPPED_SUBRESOURCE msr;
			const auto context = static_cast<ID3D11DeviceContext*>(Renderer::GetRenderContext().GetDeviceContext());
			context->Map(
			constantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr);
			memcpy(msr.pData, &data, sizeof(data));
			context->Unmap(constantBuffer.Get(), 0u);
		}

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;
	};
}
