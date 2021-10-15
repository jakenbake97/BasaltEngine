#pragma once

namespace Basalt
{
	class IWindow;

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
		virtual void DrawTestTriangle(float angle, uint32 width, uint32 height, Vector3 position) = 0;
		virtual void* GetDevice() = 0;
		virtual void* GetDeviceContext() = 0;

		static std::unique_ptr<RenderContext> CreateRenderContext(std::unique_ptr<IWindow>& window);
	};
}
