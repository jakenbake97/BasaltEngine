#pragma once

namespace Basalt
{
	enum class ShaderType
	{
		Vertex, Pixel
	};

	class Shader
	{
	public:
		Shader(const String& fileName, const ShaderType type);
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	private:
		uint32 rendererID;
	};
}
