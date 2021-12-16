#include "BEpch.h"
#include "Dx11RendererAPI.h"

#include "Dx11Context.h"
#include "Basalt/Renderer/Renderer.h"

void Basalt::Dx11RendererAPI::Clear(const Color color)
{
	// TODO: Switch to working directly off of the render target and depth stencil in the frame buffer
	Renderer::GetRenderContext().ClearColor(color);
}

void Basalt::Dx11RendererAPI::DrawIndexed(const uint32 count)
{
	static_cast<ID3D11DeviceContext*>(Renderer::GetRenderContext().GetDeviceContext())->DrawIndexed(count, 0u, 0u);
}