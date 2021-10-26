#pragma once
#include "Shader.h"
#include "Renderer.h"

namespace Basalt
{
	struct BufferAttribute
	{
		String name;
		ShaderDataType type;
		uint32 size;
		uint32 offset;
		bool normalized;

		BufferAttribute() = default;
		BufferAttribute(String name, ShaderDataType type, bool normalized = false);
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferAttribute>& attributes);

		const std::vector<BufferAttribute>& GetAttributes() const { return attributes; }
		uint32 GetStride() const { return stride; }
		uint32 GetAttributeCount() const { return (uint32)attributes.size(); }

		std::vector<BufferAttribute>::iterator begin() { return attributes.begin(); }
		std::vector<BufferAttribute>::iterator end() { return attributes.end(); }

		std::vector<BufferAttribute>::const_iterator begin() const { return attributes.begin(); }
		std::vector<BufferAttribute>::const_iterator end() const { return attributes.end(); }

		BufferAttribute operator[](const int i)
		{
			return attributes[i];
		}

	private:
		void CalculateOffsetsAndStride();

		std::vector<BufferAttribute> attributes;
		uint32 stride = 0;
	};

	class VertexBuffer
	{
	protected:
		VertexBuffer() = default;
	public:
		VertexBuffer(const VertexBuffer& other) = delete;
		VertexBuffer(VertexBuffer&& other) noexcept = delete;
		VertexBuffer& operator=(const VertexBuffer& other) = delete;
		VertexBuffer& operator=(VertexBuffer&& other) noexcept = delete;
		virtual ~VertexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetLayout(const BufferLayout& layout, const std::unique_ptr<Shader>& shader) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		template <typename T>
		static std::unique_ptr<VertexBuffer> Create(const std::vector<T>& vertices, const std::unique_ptr<Shader>& shader, const BufferLayout& layout = { {"Position", ShaderDataType::Float3} })
		{
			switch (Renderer::GetRenderAPI())
			{
			case RendererAPI::None:
				BE_ERROR("RendererAPI::None (headless) is not currently supported");
				return nullptr;
#if BE_PLATFORM_WINDOWS
			case RendererAPI::DirectX11: return std::make_unique<class Dx11VertexBuffer>(
				vertices, shader, layout);
#endif
			}
			BE_ERROR("RenderAPI ({0}) is currently set to an unknown or unsupported API on the current platform",
				Renderer::GetRenderAPI());
			return nullptr;
		}
	};

	class IndexBuffer
	{
	protected:
		IndexBuffer() = default;
	public:
		IndexBuffer(const IndexBuffer& other) = delete;
		IndexBuffer(IndexBuffer&& other) noexcept = delete;
		IndexBuffer& operator=(const IndexBuffer& other) = delete;
		IndexBuffer& operator=(IndexBuffer&& other) noexcept = delete;
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32 GetCount() const = 0;

		static std::unique_ptr<IndexBuffer> Create(std::vector<uint32> indices);
	};

#if BE_PLATFORM_WINDOWS
	template <typename T>
	class Dx11ConstantBuffer;
#endif

	template <typename T>
	class ConstantBuffer
	{
	protected:
		ConstantBuffer() = default;
	public:
		ConstantBuffer(const ConstantBuffer& other) = delete;
		ConstantBuffer(ConstantBuffer&& other) noexcept = delete;
		ConstantBuffer& operator=(const ConstantBuffer& other) = delete;
		ConstantBuffer& operator=(ConstantBuffer&& other) noexcept = delete;
		virtual ~ConstantBuffer() = default;

		virtual void Bind(ShaderType type) const = 0;
		virtual void UpdateData(const T& data) = 0;

		static std::unique_ptr<ConstantBuffer<T>> Create(const T& data);

		static std::unique_ptr<ConstantBuffer<T>> Create();
	};
}
#include "BufferTemplates.tpp"
