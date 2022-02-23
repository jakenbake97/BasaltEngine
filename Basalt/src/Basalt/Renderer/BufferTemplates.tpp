#pragma once

#ifdef BE_PLATFORM_WINDOWS
#include "Platform/DirectX11/Dx11Buffer.h"
#endif


namespace Basalt
{
	/// <summary>
	/// Creates a vertex buffer for the selected renderer API from the collection of <paramref name="vertices"/> provided and establishes it to follow the passed in <paramref name="layout"/>
	/// </summary>
	/// <typeparam name="T">The structure of the vertex layout in the <paramref name="vertices"/> collection</typeparam>
	/// <param name="vertices"> A collection of vertex data to be used to create the buffer</param>
	/// <param name="shader"> The shader to bind the vertex <paramref name="layout"/> to</param>
	/// <param name="layout"> The structure of vertex data in the buffer. Defaults to "position : float3" </param>
	/// <returns> A base class pointer to the API specific vertex buffer that was created</returns>
	template <typename T>
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(const std::vector<T>& vertices, const std::shared_ptr<Shader>& shader, const BufferLayout& layout)
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

	/// <summary>
	/// Creates a buffer of constants/uniforms for the selected rendering API that can be read from in a shader
	/// </summary>
	/// <param name="data">an item of the constant buffer template type to fill the buffer</param>
	/// <returns>A base class pointer to the API specific constant buffer that was created</returns>
	template <typename T>
	std::shared_ptr<ConstantBuffer<T>> ConstantBuffer<T>::Create(const T& data)
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

	/// <summary>
	/// Creates an empty buffer ready to accept data of the templated type T
	/// </summary>
	/// <returns>A base class pointer to the API specific constant buffer that was created</returns>
	template <typename T>
	std::shared_ptr<ConstantBuffer<T>> ConstantBuffer<T>::Create()
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
