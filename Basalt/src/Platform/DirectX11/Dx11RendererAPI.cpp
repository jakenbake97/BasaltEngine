#include "BEpch.h"
#include "Dx11RendererAPI.h"

#include "Dx11Context.h"
#include "Basalt/Renderer/Renderer.h"
#include "Basalt/Renderer/VertexArray.h"

namespace Basalt
{

	void Dx11RendererAPI::Clear(const Color color)
	{
		// TODO: Switch to working directly off of the render target and depth stencil in the frame buffer
		Renderer::GetRenderContext().ClearColor(color);
	}

	void Dx11RendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		static_cast<ID3D11DeviceContext*>(Renderer::GetRenderContext().GetDeviceContext())->DrawIndexed(vertexArray->GetIndexBuffer()->GetCount(), 0u, 0u);
	}

	void Dx11RendererAPI::SwapBuffers(const bool isVsync)
	{
		Renderer::GetRenderContext().SwapBuffers(isVsync);
	}
}
