#pragma once

#ifdef BE_PLATFORM_WINDOWS
#include "Platform/DirectX11/Dx11Buffer.h"
#endif


namespace Basalt
{
	
	template <typename T>
	Ref<VertexBuffer> VertexBuffer::Create(const std::vector<T>& vertices, const Ref<Shader>& shader, const BufferLayout& layout)
	{
		switch (Renderer::GetAPI())
		{
		case Renderer::API::None:
			BE_ERROR("RendererAPI::None (headless) is not currently supported");
			return nullptr;
#if BE_PLATFORM_WINDOWS
		case Renderer::API::DirectX11: return std::make_shared<Dx11VertexBuffer>(vertices, shader, layout);
#endif
		}
		BE_ERROR("RenderAPI ({0}) is currently set to an unknown or unsupported API on the current platform",
		         Renderer::GetAPI());
		return nullptr;
	}

	
	template <typename T>
	Ref<ConstantBuffer<T>> ConstantBuffer<T>::Create(const T& data)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			BE_ERROR("RendererAPI::None (headless) is not currently supported");
			return nullptr;
#if BE_PLATFORM_WINDOWS
		case RendererAPI::API::DirectX11: return std::make_unique<Dx11ConstantBuffer<T>>(data);
#endif
		}
		BE_ERROR("RenderAPI ({0}) is currently set to an unknown or unsupported API on the current platform",
		         Renderer::GetAPI());
		return nullptr;
	}

	
	template <typename T>
	Ref<ConstantBuffer<T>> ConstantBuffer<T>::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			BE_ERROR("RendererAPI::None (headless) is not currently supported");
			return nullptr;
#if BE_PLATFORM_WINDOWS
		case RendererAPI::API::DirectX11: return std::make_unique<Dx11ConstantBuffer<T>>();
#endif
		}
		BE_ERROR("RenderAPI ({0}) is currently set to an unknown or unsupported API on the current platform",
		         Renderer::GetAPI());
		return nullptr;
	}
}
