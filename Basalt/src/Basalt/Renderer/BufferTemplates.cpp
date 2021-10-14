#include "BEpch.h"

#ifdef BE_PLATFORM_WINDOWS 
#include "Platform/DirectX11/Dx11Buffer.h"
#endif

namespace Basalt
{
	template <typename T>
VertexBuffer* VertexBuffer::Create(const std::vector<T>& vertices, std::unique_ptr<Shader>& shader, const BufferLayout& layout)
	{
		switch (Renderer::GetRenderAPI())
		{
		case RendererAPI::None:
			BE_ERROR("RendererAPI::None (headless) is not currently supported File:{0}, Line:{1}", __FILE__,
				__LINE__);
			return nullptr;
#if BE_PLATFORM_WINDOWS
		case RendererAPI::DirectX11: return new Dx11VertexBuffer(vertices, shader, layout);
#endif
		}
		BE_ERROR("RenderAPI ({0}) is currently set to an unknown or unsupported API on the current platform",
			Renderer::GetRenderAPI());
		return nullptr;
	}
}