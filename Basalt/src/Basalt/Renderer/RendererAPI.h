#pragma once

#include "Basalt/Utility/Math.h"

namespace Basalt
{
	class VertexArray;

	class RendererAPI
	{
	public:
		/// <summary>
		/// The rendering APIs currently supported by Basalt
		/// </summary>
		enum class API
		{
			None = 0, DirectX11 = 1
		};

		virtual ~RendererAPI() = default;

		/// <summary>
		/// Clears the frame buffer to the <paramref name="color"/> parameter
		/// </summary>
		/// <param name="color">The color to clear the framebuffer to</param>
		virtual void Clear(Color color) = 0;
		
		/// <summary>
		/// Draws the mesh described in the <paramref name="vertexArray"/>
		/// </summary>
		/// <param name="vertexArray">The vertex and index data to draw based on the bound shader</param>
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0; //TODO: Eventually should pass in Mesh list

		/// <summary>
		/// Swaps the frame buffers in the selected render api. If vsync is off this happens immediately, otherwise the api waits for the next vblank
		/// </summary>
		/// <param name="isVsync">indicates if vsync is enabled or not</param>
		virtual void SwapBuffers(bool isVsync) = 0;

		/// <summary>
		/// Returns the currently selected renderer api
		/// </summary>
		/// <returns>An enum of the selected renderer api</returns>
		static API GetAPI() { return api; }
	private:
		static API api;
	};
}
