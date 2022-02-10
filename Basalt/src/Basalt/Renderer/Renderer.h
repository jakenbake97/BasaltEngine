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
		static void Initialize(std::unique_ptr<Window>& window);

		static API GetAPI(){return RendererAPI::GetAPI();}

		static RenderContext& GetRenderContext();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

	private:
		static std::unique_ptr<RenderContext> context;

		struct SceneData
		{
			Mat4x4 viewProjectionMatrix;
		};

		static std::unique_ptr<SceneData> sceneData;
	};
}
