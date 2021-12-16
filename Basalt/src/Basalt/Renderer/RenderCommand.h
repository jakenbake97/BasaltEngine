#pragma once
#include "RendererAPI.h"

namespace Basalt
{
	class RenderCommand
	{
	public:
		static void Clear(const Color color)
		{
			rendererApi->Clear(color);
		}

		static void DrawIndexed(const uint32 count)
		{
			rendererApi->DrawIndexed(count);
		}
	private:
		static RendererAPI* rendererApi;
	};
}
