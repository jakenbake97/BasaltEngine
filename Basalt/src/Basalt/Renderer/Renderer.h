#pragma once
#include "BEpch.h"
#include "RenderContext.h"

namespace Basalt
{
	class IWindow;
	//class RenderContext;

	enum class RendererAPI
	{
		None = 0,
		DirectX11 = 1
	};

	class Renderer
	{
	public:
		static void Initialize(std::unique_ptr<IWindow>& window);
		static RendererAPI GetRenderAPI() { return currentAPI; }
		static RenderContext& GetRenderContext();
	private:
		static RendererAPI currentAPI;
		static std::unique_ptr<RenderContext> context;
	};
}
