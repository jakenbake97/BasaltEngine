#pragma once

namespace Basalt
{
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32 ShaderDataTypeSize(const ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 4 * 2;
			case ShaderDataType::Float3:	return 4 * 3;
			case ShaderDataType::Float4:	return 4 * 4;
			case ShaderDataType::Mat3:		return 4 * 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;
			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;
			case ShaderDataType::Bool:		return 1;
			default: BE_ERROR("ShaderDataType {0} is unknown", type);return 0;
		}
	}

	struct BufferAttribute
	{
		String name;
		ShaderDataType type;
		uint32 size;
		uint32 offset;
		bool normalized;

		BufferAttribute() = default;
		BufferAttribute(String name, ShaderDataType type, bool normalized = false);

		uint32 GetComponentCount() const
		{
			switch (type)
			{ 
				case ShaderDataType::Float:		return 1;
				case ShaderDataType::Float2:	return 2;
				case ShaderDataType::Float3:	return 3;
				case ShaderDataType::Float4:	return 4;
				case ShaderDataType::Mat3:		return 3 * 3;
				case ShaderDataType::Mat4:		return 4 * 4;
				case ShaderDataType::Int:		return 1;
				case ShaderDataType::Int2:		return 2;
				case ShaderDataType::Int3:		return 3;
				case ShaderDataType::Int4:		return 4;
				case ShaderDataType::Bool:		return 1;
				default: BE_ERROR("ShaderDataType {0} is unknown", type);return 0;
			}
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferAttribute>& attributes);
		
		const std::vector<BufferAttribute>& GetAttributes() const { return attributes; }
		uint32 GetStride() const { return stride; }

		std::vector<BufferAttribute>::iterator begin() { return attributes.begin(); }
		std::vector<BufferAttribute>::iterator end() { return attributes.end(); }

		std::vector<BufferAttribute>::const_iterator begin() const { return attributes.begin(); }
		std::vector<BufferAttribute>::const_iterator end() const { return attributes.end(); }
	private:
		void CalculateOffsetsAndStride();

		std::vector<BufferAttribute> attributes;
		uint32 stride = 0;
	};

	class VertexBuffer
	{
	protected:
		VertexBuffer() = default;
	public:
		VertexBuffer(const VertexBuffer& other) = delete;
		VertexBuffer(VertexBuffer&& other) noexcept = delete;
		VertexBuffer& operator=(const VertexBuffer& other) = delete;
		VertexBuffer& operator=(VertexBuffer&& other) noexcept = delete;
		virtual ~VertexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(const std::vector<struct Vertex>& vertices);
	};

	class IndexBuffer
	{
	protected:
		IndexBuffer() = default;
	public:
		IndexBuffer(const IndexBuffer& other) = delete;
		IndexBuffer(IndexBuffer&& other) noexcept = delete;
		IndexBuffer& operator=(const IndexBuffer& other) = delete;
		IndexBuffer& operator=(IndexBuffer&& other) noexcept = delete;
		virtual  ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32 GetCount() const = 0;

		static IndexBuffer* Create(std::vector<uint32> indices);
	};
}
