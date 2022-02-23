#include "BEpch.h"
#include "Buffer.h"

#include <utility>

#ifdef BE_PLATFORM_WINDOWS 
#include "Platform/DirectX11/Dx11Buffer.h"
#endif

namespace Basalt
{
	BufferAttribute::BufferAttribute(String name, const ShaderDataType type, bool normalized)
		: name(std::move(name)), type(type), size(Shader::ShaderDataTypeSize(type)), offset(0), normalized(normalized)
	{
	}

	BufferLayout::BufferLayout(const std::initializer_list<BufferAttribute>& attributes)
		: attributes(attributes)
	{
		CalculateOffsetsAndStride();
	}

	void BufferLayout::CalculateOffsetsAndStride()
	{
		uint32 offset = 0;
		stride = 0;
		for (auto& attribute : attributes)
		{
			attribute.offset = offset;
			offset += attribute.size;
			stride += attribute.size;
		}
	}

	/// <summary>
	/// Creates an Index buffer for the currently selected API from the passed collection of <paramref name="indices"/>
	/// </summary>
	/// <param name="indices">A collection of index values to be used in the buffer</param>
	/// <returns>a base class pointer to the API specific buffer that is created</returns>
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(std::vector<uint32> indices)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			BE_ERROR("RendererAPI::None (headless) is not currently supported");
			return nullptr;
#if BE_PLATFORM_WINDOWS
		case RendererAPI::API::DirectX11: return std::make_unique<Dx11IndexBuffer>(indices);
#endif
		}

		BE_ERROR("RenderAPI ({0}) is currently set to an unknown or unsupported API on the current platform",
		         Renderer::GetAPI());
		return nullptr;
	}
}
