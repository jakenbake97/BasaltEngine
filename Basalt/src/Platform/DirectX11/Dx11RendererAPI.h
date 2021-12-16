#pragma once
#include "Basalt/Renderer/RendererAPI.h"

namespace Basalt
{
	class Dx11RendererAPI : public RendererAPI
	{
	public:
		void Clear(Color color) override;
		void DrawIndexed(uint32 count) override;
	};
}
