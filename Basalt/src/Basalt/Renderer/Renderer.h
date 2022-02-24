#pragma once
#include "RenderContext.h"
#include "RenderCommand.h"

namespace Basalt
{
	class Shader;
	class OrthographicCamera;
	class Window;
	class VertexArray;

	class Renderer
	{
	public:
		using API = RendererAPI::API;
		static void Initialize(const Window& window);

		static API GetAPI(){return RendererAPI::GetAPI();}

		static RenderContext& GetRenderContext();

		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

	private:
		static std::unique_ptr<RenderContext> context;

		struct SceneData
		{
			Mat4x4 viewProjectionMatrix;
		};
	};
}
