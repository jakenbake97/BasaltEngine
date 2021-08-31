#include "BEpch.h"
#include "Shader.h"

#include "Renderer.h"

Basalt::Shader::Shader(const String& fileName, const ShaderType type)
{
	switch (Renderer::GetRenderAPI())
	{
	case RendererAPI::None: BE_ERROR("RendererAPI::None (headless) is currently not supported");
	}
}
