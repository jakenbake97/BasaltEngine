#include "BEpch.h"
#include "VertexArray.h"

Basalt::VertexArray::VertexArray(std::shared_ptr<VertexBuffer> vertexBuffer,
                                 std::shared_ptr<IndexBuffer> indexBuffer)
		: vertBuffer(std::move(vertexBuffer)), idxBuffer(std::move(indexBuffer))
{
}

void Basalt::VertexArray::Bind() const
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

void Basalt::VertexArray::SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	vertBuffer = vertexBuffer;
}

void Basalt::VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	idxBuffer = indexBuffer;
}

const std::shared_ptr<Basalt::VertexBuffer>& Basalt::VertexArray::GetVertexBuffer() const
{
	return vertBuffer;
}

const std::shared_ptr<Basalt::IndexBuffer>& Basalt::VertexArray::GetIndexBuffer()
{
	return idxBuffer;
}
