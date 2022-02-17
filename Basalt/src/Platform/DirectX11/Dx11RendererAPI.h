#pragma once
#include "Basalt/Renderer/RendererAPI.h"

namespace Basalt
{
	class Dx11RendererAPI : public RendererAPI
	{
	public:
		void Clear(Color color) override;
		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

		void SwapBuffers(bool isVsync) override;
	};
}
