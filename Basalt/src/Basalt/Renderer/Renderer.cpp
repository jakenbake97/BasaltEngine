#include "BEpch.h"
#include "Renderer.h"

#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Basalt/Window.h"

namespace Basalt
{
	Scope<RenderContext> Renderer::context;

	void Renderer::Initialize(const Window& window)
	{
		context = RenderContext::CreateRenderContext(window);
	}

	RenderContext& Renderer::GetRenderContext()
	{
		return *context;
	}

	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray)
	{
		shader->Bind();
		vertexArray->Bind();

		RenderCommand::DrawIndexed(vertexArray);
	}
}
