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
		uint32 GetAttributeCount() const { return attributes.size(); }

		std::vector<BufferAttribute>::iterator begin() { return attributes.begin(); }
		std::vector<BufferAttribute>::iterator end() { return attributes.end(); }

		std::vector<BufferAttribute>::const_iterator begin() const { return attributes.begin(); }
		std::vector<BufferAttribute>::const_iterator end() const { return attributes.end(); }

		BufferAttribute operator[] (const int i)
		{
			return attributes[i];
		}
		
	private:
		void CalculateOffsetsAndStride();

		std::vector<BufferAttribute> attributes;
		uint32 stride = 0;
	};

	class Dx11VertexBuffer;

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

		virtual void SetLayout(const BufferLayout& layout, std::unique_ptr<Shader>& shader) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		template <typename T>
		static VertexBuffer* Create(const std::vector<T>& vertices, std::unique_ptr<Shader>& shader, const BufferLayout& layout = { {"Position", ShaderTypes::ShaderDataType::Float3} });
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

		static IndexBuffer* Create(std::vector<uint32> indices);
	};
}
#include "BufferTemplates.cpp"