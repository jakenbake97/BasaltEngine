#include "BEpch.h"
#include "RenderCommand.h"

#include "Platform/DirectX11/Dx11RendererAPI.h"

namespace Basalt
{
	RendererAPI* RenderCommand::rendererApi = new Dx11RendererAPI;
}
