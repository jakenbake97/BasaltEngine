#pragma once
#include "Buffer.h"

namespace Basalt
{
	class VertexArray
	{
	public:
		VertexArray() = default;
		VertexArray(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer);

		void Bind() const;

		void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

		const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const;
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer();

	private:
		std::shared_ptr<VertexBuffer> vertBuffer;
		std::shared_ptr<IndexBuffer> idxBuffer;
	};
}
