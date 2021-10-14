#pragma once

namespace Basalt
{
	class RenderContext
	{
	protected:
		RenderContext() = default;
	public:
		RenderContext(const RenderContext& other) = delete;
		RenderContext(RenderContext&& other) noexcept = delete;
		RenderContext& operator=(const RenderContext& other) = delete;
		RenderContext& operator=(RenderContext&& other) noexcept = delete;
		virtual ~RenderContext() = default;
		
		virtual void SwapBuffers() = 0;
		virtual void ClearColor(Color color) = 0;
		virtual void DrawTestTriangle(float angle, float aspectRatio) = 0;
		virtual void* GetDevice() = 0;
		virtual void* GetDeviceContext() = 0;

		static std::unique_ptr<RenderContext> CreateRenderContext(void* handle);
	};
}
