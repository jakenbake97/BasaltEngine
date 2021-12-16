#pragma once
#include "RenderContext.h"
#include "RenderCommand.h"

namespace Basalt
{
	class Window;

	class Renderer
	{
	public:
		using API = RendererAPI::API;
		static void Initialize(std::unique_ptr<Window>& window);

		static API GetAPI(){return RendererAPI::GetAPI();}

		static RenderContext& GetRenderContext();

		static void BeginScene();
		static void EndScene();

	private:
		static std::unique_ptr<RenderContext> context;
	};
}
