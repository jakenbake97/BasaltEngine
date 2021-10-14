#pragma once
#include <dxgiformat.h>

namespace Basalt
{
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
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static std::unique_ptr<Shader> Create(const String& vertexSource, const String& fragmentSource);

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

	private:
	};
}
