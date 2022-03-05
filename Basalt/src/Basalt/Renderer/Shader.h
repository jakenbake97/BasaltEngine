#pragma once

namespace Basalt
{
		/// <summary>
		/// The type/stage of the shader
		/// </summary>
		enum class ShaderType
		{
			None = 0,
			Vertex,
			Fragment
		};

		/// <summary>
		/// The data types supported in the shader. Used for filling a buffer layout
		/// </summary>
		enum class ShaderDataType
		{
			None = 0,
			Float,
			Float2,
			Float3,
			Float4,
			Mat3,
			Mat4,
			Char,
			Char2,
			Char4,
			UChar,
			UChar2,
			UChar4,
			Short,
			Short2,
			Short4,
			UShort,
			UShort2,
			UShort4,
			Int,
			Int2,
			Int3,
			Int4,
			UInt,
			UInt2,
			UInt3,
			UInt4,
			Bool
		};

	class Shader
	{
	protected:
		Shader() = default;
	public:
		Shader(const Shader& other) = delete;
		Shader(Shader&& other) noexcept = delete;
		Shader& operator=(const Shader& other) = delete;
		Shader& operator=(Shader&& other) noexcept = delete;
		virtual ~Shader() = default;

		/// <summary>
		/// Binds the shader to the selected render pipeline
		/// </summary>
		virtual void Bind() const = 0;

		/// <summary>
		/// Removes the binding of the shader to the selected render pipeline
		/// </summary>
		virtual void Unbind() const = 0;

		/// <summary>
		/// Creates a shader for the selected renderer api from vertex and fragment/pixel shader programs
		/// </summary>
		/// <param name="vertexSource">The file to use as the vertex shader</param>
		/// <param name="fragmentSource">The file to use as the fragment/pixel shader</param>
		/// <returns>A pointer to the Basalt Shader that was created</returns>
		static std::shared_ptr<Shader> Create(const String& vertexSource, const String& fragmentSource);

		/// <summary>
		/// Returns the size of a shader data type. This is useful for calculating the stride and offset of buffer layouts
		/// </summary>
		/// <param name="type">The data type to get the size of</param>
		/// <returns>The size of <paramref name="type"/></returns>
		static constexpr uint32 ShaderDataTypeSize(const ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float: return 4;
			case ShaderDataType::Float2: return 4 * 2;
			case ShaderDataType::Float3: return 4 * 3;
			case ShaderDataType::Float4: return 4 * 4;
			case ShaderDataType::Mat3: return 4 * 3 * 3;
			case ShaderDataType::Mat4: return 4 * 4 * 4;
			case ShaderDataType::Char: return 1;
			case ShaderDataType::Char2: return 1 * 2;
			case ShaderDataType::Char4: return 1 * 4;
			case ShaderDataType::UChar: return 1;
			case ShaderDataType::UChar2: return 1 * 2;
			case ShaderDataType::UChar4: return 1 * 4;
			case ShaderDataType::Short: return 2;
			case ShaderDataType::Short2: return 2 * 2;
			case ShaderDataType::Short4: return 2 * 4;
			case ShaderDataType::UShort: return 2;
			case ShaderDataType::UShort2: return 2 * 2;
			case ShaderDataType::UShort4: return 2 * 4;
			case ShaderDataType::Int: return 4;
			case ShaderDataType::Int2: return 4 * 2;
			case ShaderDataType::Int3: return 4 * 3;
			case ShaderDataType::Int4: return 4 * 4;
			case ShaderDataType::UInt: return 4;
			case ShaderDataType::UInt2: return 4 * 2;
			case ShaderDataType::UInt3: return 4 * 3;
			case ShaderDataType::UInt4: return 4 * 4;
			case ShaderDataType::Bool: return 1;
			default: BE_ERROR("ShaderDataType {0} is unknown", type);
				return 0;
			}
		}

		/// <summary>
		/// Returns the number of components in the <paramref name="type"/> shader data type
		/// </summary>
		/// <param name="type">The data type to get the number of components of</param>
		/// <returns>The number of components that make up <paramref name="type"/></returns>
		static constexpr uint32 GetShaderDataTypeComponentCount(const ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float: return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;
			case ShaderDataType::Mat3: return 3 * 3;
			case ShaderDataType::Mat4: return 4 * 4;
			case ShaderDataType::Char: return 1;
			case ShaderDataType::Char2: return 2;
			case ShaderDataType::Char4: return 4;
			case ShaderDataType::UChar: return 1;
			case ShaderDataType::UChar2: return 2;
			case ShaderDataType::UChar4: return 4;
			case ShaderDataType::Short: return 1;
			case ShaderDataType::Short2: return 2;
			case ShaderDataType::Short4: return 4;
			case ShaderDataType::UShort: return 1;
			case ShaderDataType::UShort2: return 2;
			case ShaderDataType::UShort4: return 4;
			case ShaderDataType::Int: return 1;
			case ShaderDataType::Int2: return 2;
			case ShaderDataType::Int3: return 3;
			case ShaderDataType::Int4: return 4;
			case ShaderDataType::UInt: return 1;
			case ShaderDataType::UInt2: return 2;
			case ShaderDataType::UInt3: return 3;
			case ShaderDataType::UInt4: return 4;
			case ShaderDataType::Bool: return 1;
			default: BE_ERROR("ShaderDataType {0} is unknown", type);
				return 0;
			}
		}
	};
}
