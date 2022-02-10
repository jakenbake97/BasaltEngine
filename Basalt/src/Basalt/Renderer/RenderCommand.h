#pragma once
#include "RendererAPI.h"

namespace Basalt
{
	class RenderCommand
	{
	public:
		static void Clear(const Color color = { 0.25f, 0.25f, 0.5f, 1.0f })
		{
			rendererApi->Clear(color);
		}

		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			rendererApi->DrawIndexed(vertexArray);
		}

		static void SwapBuffers()
		{
			rendererApi->SwapBuffers();
		}
	private:
		static RendererAPI* rendererApi;
	};
}
