#pragma once
#include "Basalt/Utility/Math.h"

namespace Basalt
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, DirectX11 = 1
		};
	public:
		virtual ~RendererAPI() = default;
		virtual void Clear(Color color = { 0.25f, 0.25f, 0.5f, 1.0f }) = 0;

		//TODO: Eventually should pass in Mesh list
		virtual void DrawIndexed(uint32 count) = 0;

		static API GetAPI() { return api; }
	private:
		static API api;
	};
}
