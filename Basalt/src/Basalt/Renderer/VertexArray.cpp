#include "BEpch.h"
#include "VertexArray.h"

namespace Basalt
{
	VertexArray::VertexArray(Ref<VertexBuffer> vertexBuffer,
		Ref<IndexBuffer> indexBuffer)
		: vertBuffer(std::move(vertexBuffer)), idxBuffer(std::move(indexBuffer))
	{
	}

	void VertexArray::Bind() const
	{
		if (vertBuffer != nullptr)
		{
			vertBuffer->Bind();
		}
		if (idxBuffer != nullptr)
		{
			idxBuffer->Bind();
		}
	}

	void VertexArray::SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		vertBuffer = vertexBuffer;
	}

	void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		idxBuffer = indexBuffer;
	}

	const Ref<VertexBuffer>& VertexArray::GetVertexBuffer() const
	{
		return vertBuffer;
	}

	const Ref<IndexBuffer>& VertexArray::GetIndexBuffer() const
	{
		return idxBuffer;
	}
}