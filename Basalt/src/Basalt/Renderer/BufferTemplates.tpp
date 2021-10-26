#pragma once

#ifdef BE_PLATFORM_WINDOWS
#include "Platform/DirectX11/Dx11Buffer.h"
#endif


namespace Basalt
{
	template <typename T>
	std::unique_ptr<VertexBuffer> VertexBuffer::Create(const std::vector<T>& vertices, const std::unique_ptr<Shader>& shader, const BufferLayout& layout)
		{
			switch (Renderer::GetRenderAPI())
			{
			case RendererAPI::None:
				BE_ERROR("RendererAPI::None (headless) is not currently supported");
				return nullptr;
#if BE_PLATFORM_WINDOWS
			case RendererAPI::DirectX11: return std::make_unique<class Dx11VertexBuffer>(
					vertices, shader, layout);
#endif
			}
			BE_ERROR("RenderAPI ({0}) is currently set to an unknown or unsupported API on the current platform",
			         Renderer::GetRenderAPI());
			return nullptr;
		}

	template <typename T>
	std::unique_ptr<ConstantBuffer<T>> ConstantBuffer<T>::Create(const T& data)
	{
		switch (Renderer::GetRenderAPI())
		{
		case RendererAPI::None:
			BE_ERROR("RendererAPI::None (headless) is not currently supported");
			return nullptr;
#if BE_PLATFORM_WINDOWS
		case RendererAPI::DirectX11: return std::make_unique<Dx11ConstantBuffer<T>>(data);
#endif
		}
		BE_ERROR("RenderAPI ({0}) is currently set to an unknown or unsupported API on the current platform",
		         Renderer::GetRenderAPI());
		return nullptr;
	}

	template <typename T>
	std::unique_ptr<ConstantBuffer<T>> ConstantBuffer<T>::Create()
	{
		switch (Renderer::GetRenderAPI())
		{
		case RendererAPI::None:
			BE_ERROR("RendererAPI::None (headless) is not currently supported");
			return nullptr;
#if BE_PLATFORM_WINDOWS
		case RendererAPI::DirectX11: return std::make_unique<Dx11ConstantBuffer<T>>();
#endif
		}
		BE_ERROR("RenderAPI ({0}) is currently set to an unknown or unsupported API on the current platform",
			Renderer::GetRenderAPI());
		return nullptr;
	}
}
