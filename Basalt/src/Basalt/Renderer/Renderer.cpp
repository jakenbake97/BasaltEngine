#include "BEpch.h"
#include "Renderer.h"

#include "RenderContext.h"

namespace Basalt
{
	// TODO: Set at runtime instead of hardcoding
	RendererAPI Renderer::currentAPI = RendererAPI::DirectX11;

	std::unique_ptr<RenderContext> Renderer::context;

	void Renderer::Initialize(void* windowHandle)
	{
		context = RenderContext::CreateRenderContext(windowHandle);
	}

	RenderContext& Renderer::GetRenderContext()
	{
		return *context;
	}
}
