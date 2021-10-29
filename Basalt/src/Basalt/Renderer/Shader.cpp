#include "BEpch.h"
#include "Shader.h"

#include "Renderer.h"
#ifdef BE_PLATFORM_WINDOWS
#include "Platform/DirectX11/Dx11Shader.h"
#endif


namespace Basalt
{
	std::unique_ptr<Shader> Shader::Create(const String& vertexSource,  const String& fragmentSource)
	{
		switch (Renderer::GetRenderAPI())
		{
		case RendererAPI::None: BE_ERROR("RendererAPI::None is not currently supported"); return nullptr;
#ifdef BE_PLATFORM_WINDOWS
		case RendererAPI::DirectX11: return std::make_unique<Dx11Shader>(vertexSource,
			fragmentSource);
#endif
		}

		BE_ERROR("Unknown RendererAPI {0}", Renderer::GetRenderAPI());
		return nullptr;
	}
}
