#include "BEpch.h"
#include "Shader.h"

#include <utility>

#include "Renderer.h"
#include "Platform/DirectX11/Dx11Shader.h"

namespace Basalt
{
	std::unique_ptr<Shader> Shader::Create(const String& vertexSource,  const String& fragmentSource)
	{
		switch (Renderer::GetRenderAPI())
		{
		case RendererAPI::None: BE_ERROR("RendererAPI::None is not currently supported"); return nullptr;
		case RendererAPI::DirectX11: return std::make_unique<Dx11Shader>(Dx11Shader(vertexSource,
			fragmentSource));
		}

		BE_ERROR("Unknown RendererAPI");
		return nullptr;
	}
}
