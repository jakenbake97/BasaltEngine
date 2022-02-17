#pragma once

#include "Basalt/Utility/Math.h"

namespace Basalt
{
	class VertexArray;

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, DirectX11 = 1
		};
	public:
		virtual ~RendererAPI() = default;
		virtual void Clear(Color color) = 0;

		//TODO: Eventually should pass in Mesh list
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		virtual void SwapBuffers(bool isVsync) = 0;

		static API GetAPI() { return api; }
	private:
		static API api;
	};
}
