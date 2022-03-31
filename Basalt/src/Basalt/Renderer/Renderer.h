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

		/// <summary>
		/// Initializes the renderer and creates the api specific context for the selected api
		/// </summary>
		/// <param name="window">The application window to render to</param>
		static void Initialize(const Window& window);

		/// <summary>
		/// Returns the currently selected renderer api
		/// </summary>
		/// <returns>an enum indicating the selected api</returns>
		static API GetAPI(){return RendererAPI::GetAPI();}

		/// <summary>
		/// Returns the render context interface
		/// </summary>
		/// <returns>a reference to the render context interface</returns>
		static RenderContext& GetRenderContext();

		/// <summary>
		/// Prepares for rendering the scene in a current frame
		/// </summary>
		static void BeginScene();

		/// <summary>
		/// Marks the end of render commands for a scene in the current frame
		/// </summary>
		static void EndScene();

		/// <summary>
		/// Submits a draw call to the selected render api
		/// </summary>
		/// <param name="shader">The shader to use when rendering</param>
		/// <param name="vertexArray">The vertex and index data to render</param>
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray);

	private:
		static Scope<RenderContext> context;

		struct SceneData
		{
			Mat4x4 viewProjectionMatrix;
		};
	};
}
