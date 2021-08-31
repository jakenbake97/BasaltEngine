#pragma once

namespace Basalt
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static VertexBuffer* Create(const std::vector<struct Vertex>& vertices);
	};

	class IndexBuffer
	{
	public:
		virtual  ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32 GetCount() const = 0;

		static IndexBuffer* Create(std::vector<uint32> indices);
	};
}
