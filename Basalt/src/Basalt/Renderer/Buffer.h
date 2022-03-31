#pragma once
#include "Shader.h"
#include "Renderer.h"

namespace Basalt
{
	/// <summary>
	/// Descriptor of an attribute to be added to a buffer layout
	/// </summary>
	struct BufferAttribute
	{
		String name;
		ShaderDataType type = ShaderDataType::None;
		uint32 size{};
		uint32 offset{};
		bool normalized{};

		/// <summary>
		/// Creates a default buffer attribute to be used in a buffer layout
		/// </summary>
		BufferAttribute() = default;
		/// <summary>
		/// Creates a buffer attribute to be used in a buffer layout with the provided parameters
		/// </summary>
		/// <param name="name">The name of this attribute</param>
		/// <param name="type">The type of data this attribute represents</param>
		/// <param name="normalized">Should the values of this attribute be normalized</param>
		BufferAttribute(String name, ShaderDataType type, bool normalized = false);
	};

	/// <summary>
	/// Used to describe the layout of a vertex buffer via attributes
	/// </summary>
	class BufferLayout
	{
	public:
		/// <summary>
		/// Constructs a default bufferLayout with no attributes
		/// </summary>
		BufferLayout() = default;

		/// <summary>
		/// Constructs a layout from a list of buffer attributes 
		/// </summary>
		/// <param name="attributes">initializer list of buffer attributes</param>
		BufferLayout(const std::initializer_list<BufferAttribute>& attributes);

		/// <summary>
		/// Returns the current attributes in this layout
		/// </summary>
		/// <returns>a vector collection of the attributes in the layout</returns>
		const std::vector<BufferAttribute>& GetAttributes() const { return attributes; }

		/// <summary>
		/// Returns the stride between elements in the buffer, the stride is calculated as the size of all the attributes
		/// </summary>
		/// <returns>the size of a single element using this layout</returns>
		uint32 GetStride() const { return stride; }

		/// <summary>
		/// Returns the number of attributes currently in this layout
		/// </summary>
		/// <returns>number of attributes in the layout vector</returns>
		uint32 GetAttributeCount() const { return (uint32)attributes.size(); }

		/// <summary>
		/// Returns an iterator at the beginning of the attributes collection
		/// </summary>
		/// <returns>iterator at the first element of the attributes vector</returns>
		std::vector<BufferAttribute>::iterator begin() { return attributes.begin(); }

		/// <summary>
		/// Returns an iterator at the end of the attributes collection
		/// </summary>
		/// <returns>iterator at the last element of the attributes vector</returns>
		std::vector<BufferAttribute>::iterator end() { return attributes.end(); }

		/// <summary>
		/// Returns a constant iterator at the beginning of the attributes collection
		/// </summary>
		/// <returns>const iterator at the first element of the attributes vector</returns>
		std::vector<BufferAttribute>::const_iterator begin() const { return attributes.begin(); }

		/// <summary>
		/// Returns a constant iterator at the end of the attributes collection
		/// </summary>
		/// <returns>const iterator at the last element of the attributes vector</returns>
		std::vector<BufferAttribute>::const_iterator end() const { return attributes.end(); }

		/// <summary>
		///	Used as a direct indexer of the underlying attributes collection
		/// </summary>
		/// <param name="i">The index into the collection</param>
		/// <returns>the attribute at the index i</returns>
		BufferAttribute operator[](const int i)
		{
			return attributes[i];
		}

	private:
		void CalculateOffsetsAndStride();

		std::vector<BufferAttribute> attributes;
		uint32 stride = 0;
	};

	/// <summary>
	/// A render api agnostic vertex buffer that can take any defined layout
	/// </summary>
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

		/// <summary>
		/// Binds the vertex buffer to the currently selected render api
		/// </summary>
		virtual void Bind() = 0;

		/// <summary>
		/// Removes the binding of the vertex buffer from the currently selected render api
		/// </summary>
		virtual void Unbind() = 0;

		/// <summary>
		/// Sets the layout of the buffer and associates it with a shader
		/// </summary>
		/// <param name="layout">The new layout for the buffer</param>
		/// <param name="shader">The shader to associate this buffer with</param>
		virtual void SetLayout(const BufferLayout& layout, const Ref<Shader>& shader) = 0;

		/// <summary>
		/// Returns the current buffer layout
		/// </summary>
		/// <returns>The BufferLayout describing the current layout of this vertex buffer</returns>
		virtual const BufferLayout& GetLayout() const = 0;

		/// <summary>
		/// Creates a vertex buffer for the selected renderer API from the collection of <paramref name="vertices"/> provided and establishes it to follow the passed in <paramref name="layout"/>
		/// </summary>
		/// <typeparam name="T">The structure of the vertex layout in the <paramref name="vertices"/> collection</typeparam>
		/// <param name="vertices"> A collection of vertex data to be used to create the buffer</param>
		/// <param name="shader"> The shader to bind the vertex <paramref name="layout"/> to</param>
		/// <param name="layout"> The structure of vertex data in the buffer. Defaults to "position : float3" </param>
		/// <returns> A base class pointer to the API specific vertex buffer that was created</returns>
		template <typename T>
		static std::shared_ptr<VertexBuffer> Create(const std::vector<T>& vertices,
		                                            const Ref<Shader>& shader,
		                                            const BufferLayout& layout = {
			                                            {"Position", ShaderDataType::Float3}
		                                            });
	};

	/// <summary>
	/// a render api agnostic index buffer
	/// </summary>
	class IndexBuffer
	{
	protected:
		IndexBuffer() = default;
	public:
		IndexBuffer(const IndexBuffer& other) = delete;
		IndexBuffer(IndexBuffer&& other) noexcept = delete;
		IndexBuffer& operator=(const IndexBuffer& other) = delete;
		IndexBuffer& operator=(IndexBuffer&& other) noexcept = delete;
		virtual ~IndexBuffer() = default;

		/// <summary>
		/// Binds the index buffer to the currently selected render api
		/// </summary>
		virtual void Bind() const = 0;

		/// <summary>
		/// Removes the binding of the index buffer from the currently selected render api
		/// </summary>
		virtual void Unbind() const = 0;

		/// <summary>
		/// Returns the number of indices in this index buffer
		/// </summary>
		/// <returns></returns>
		virtual uint32 GetCount() const = 0;

		/// <summary>
		/// Creates an Index buffer for the currently selected API from the passed collection of <paramref name="indices"/>
		/// </summary>
		/// <param name="indices">A collection of index values to be used in the buffer</param>
		/// <returns>a base class pointer to the API specific buffer that is created</returns>
		static Ref<IndexBuffer> Create(std::vector<uint32> indices);
	};

	/// <summary>
	/// A buffer of data that can be sent to a shader to modify its properties
	/// </summary>
	/// <typeparam name="T">The type of data in the buffer</typeparam>
	template <typename T>
	class ConstantBuffer
	{
	protected:
		ConstantBuffer() = default;
	public:
		ConstantBuffer(const ConstantBuffer& other) = delete;
		ConstantBuffer(ConstantBuffer&& other) noexcept = delete;
		ConstantBuffer& operator=(const ConstantBuffer& other) = delete;
		ConstantBuffer& operator=(ConstantBuffer&& other) noexcept = delete;
		virtual ~ConstantBuffer() = default;

		/// <summary>
		/// Binds the constant buffer to a shader stage
		/// </summary>
		/// <param name="type">The type of shader/stage to bind the buffer</param>
		virtual void Bind(ShaderType type) const = 0;

		/// <summary>
		/// Updates the buffer to use the new data
		/// </summary>
		/// <param name="data">the data to set the buffer to</param>
		virtual void UpdateData(const T& data) = 0;

		/// <summary>
		/// Creates a buffer of constants/uniforms for the selected rendering API that can be read from in a shader
		/// </summary>
		/// <param name="data">an item of the constant buffer template type to fill the buffer</param>
		/// <returns>A base class pointer to the API specific constant buffer that was created</returns>
		static Ref<ConstantBuffer<T>> Create(const T& data);

		/// <summary>
		/// Creates an empty buffer ready to accept data of the templated type T
		/// </summary>
		/// <returns>A base class pointer to the API specific constant buffer that was created</returns>
		static Ref<ConstantBuffer<T>> Create();
	};
}

#include "BufferTemplates.tpp"
