#include "BEpch.h"
#include "Renderer.h"

#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Basalt/Window.h"

namespace Basalt
{
	std::unique_ptr<RenderContext> Renderer::context;

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

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		vertexArray->Bind();

		RenderCommand::DrawIndexed(vertexArray);
	}
}
