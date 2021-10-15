#include "BEpch.h"
#include "Renderer.h"

#include "RenderContext.h"
#include "Basalt/IWindow.h"

namespace Basalt
{
	// TODO: Set at runtime instead of hardcoding
	RendererAPI Renderer::currentAPI = RendererAPI::DirectX11;

	std::unique_ptr<RenderContext> Renderer::context;

	void Renderer::Initialize(std::unique_ptr<IWindow>& window)
	{
		context = RenderContext::CreateRenderContext(window);
	}

	RenderContext& Renderer::GetRenderContext()
	{
		return *context;
	}
}
