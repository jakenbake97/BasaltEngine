#pragma once
#include "Buffer.h"

namespace Basalt
{
	/// <summary>
	/// A combination of a vertex buffer and an index buffer, basically the precursor to a mesh class
	/// </summary>
	class VertexArray
	{
	public:
		/// <summary>
		/// Constructs a default empty vertex array
		/// </summary>
		VertexArray() = default;

		/// <summary>
		/// Constructs a vertex array with the vertices and indices to draw a mesh
		/// </summary>
		/// <param name="vertexBuffer">The vertex data for the mesh</param>
		/// <param name="indexBuffer">The indices of the mesh</param>
		VertexArray(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer);

		/// <summary>
		/// Binds the vertex and index buffers to the pipeline
		/// </summary>
		void Bind() const;

		/// <summary>
		/// Sets the member vertex buffer to the one passed in <paramref name="vertexBuffer"/>
		/// </summary>
		/// <param name="vertexBuffer">The new vertex buffer to point to in the vertex array</param>
		void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);

		/// <summary>
		/// Sets the member index buffer to the one passed in <paramref name="indexBuffer"/>
		/// </summary>
		/// <param name="indexBuffer">The new index buffer to point to in the vertex array</param>
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

		/// <summary>
		/// Returns the current vertex buffer in the array
		/// </summary>
		/// <returns>A shared pointer to the stored vertex buffer</returns>
		const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const;

		/// <summary>
		/// Returns the current index buffer in the array
		/// </summary>
		/// <returns>A shared pointer to the stored index buffer</returns>
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const;

	private:
		std::shared_ptr<VertexBuffer> vertBuffer;
		std::shared_ptr<IndexBuffer> idxBuffer;
	};
}
