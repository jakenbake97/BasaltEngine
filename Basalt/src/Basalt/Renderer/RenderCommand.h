#pragma once
#include "RendererAPI.h"

namespace Basalt
{
	class RenderCommand
	{
	public:
		/// <summary>
		/// Commands the selected rendering api to clear the frame buffer
		/// </summary>
		/// <param name="color">option color to clear the buffer to</param>
		static void Clear(const Color color = { 0.25f, 0.25f, 0.5f, 1.0f })
		{
			rendererApi->Clear(color);
		}

		/// <summary>
		/// Commands the selected rendering api to draw the mesh in the vertex array
		/// </summary>
		/// <param name="vertexArray">the vertex data for the mesh (vertex buffer and index buffer)</param>
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			rendererApi->DrawIndexed(vertexArray);
		}

		/// <summary>
		/// Commands the selected rendering api to swap frame buffers. If vsync is off this happens immediately, otherwise the api waits for the next vblank
		/// </summary>
		/// <param name="isVsync">indicates if vsync is enabled or not</param>
		static void SwapBuffers(bool isVsync)
		{
			rendererApi->SwapBuffers(isVsync);
		}
	private:
		static RendererAPI* rendererApi;
	};
}
