#pragma once

#include <CodeAnalysis/Warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#include "glm/mat2x2.hpp"
#include "glm/mat3x3.hpp"
#include "glm/mat4x4.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning( pop )

namespace Basalt
{
	// Math Types
	using Vector2 = glm::vec2;
	using Vector2Int = glm::ivec2;
	using Vector3 = glm::vec3;
	using Vector3Int = glm::ivec3;
	using Vector4 = glm::vec4;
	using Color = Vector4;
	using ByteColor = glm::vec<4, char>;
	using Vector4Int = glm::ivec4;
	using Mat2x2 = glm::mat2;
	using Mat3x3 = glm::mat3;
	using Mat4x4 = glm::mat4;

	// Int Types
	using uint8 = glm::uint8;
	using uint16 = glm::uint16;
	using uint32 = glm::uint32;
	using uint64 = glm::uint64;

	using int8 = glm::int8;
	using int16 = glm::int16;
	using int32 = glm::int32;
	using int64 = glm::int64;
}

namespace std
{
	inline std::ostream& operator<<(std::ostream& os, const glm::vec2& vec)
	{
		return os << "(" << vec.x << ", " << vec.y << ")";
	}

	inline std::ostream& operator<<(std::ostream& os, const glm::ivec2& vec)
	{
		return os << "(" << vec.x << ", " << vec.y << ")";
	}

	inline std::ostream& operator<<(std::ostream& os, const glm::vec3& vec)
	{
		return os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	}

	inline std::ostream& operator<<(std::ostream& os, const glm::ivec3& vec)
	{
		return os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	}

	inline std::ostream& operator<<(std::ostream& os, const glm::vec4& vec)
	{
		return os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
	}

	inline std::ostream& operator<<(std::ostream& os, const glm::ivec4& vec)
	{
		return os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
	}

	inline std::ostream& operator<<(std::ostream& os, const glm::vec<4, char> vec)
	{
		return os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
	}

	inline std::ostream& operator<<(std::ostream& os, const glm::mat2& mat)
	{
		return os << "\n{" << mat[0][0] << "\t" << mat[0][1] << "\n"
			<< mat[1][0] << "\t" << mat[1][1] << "}";
	}

	inline std::ostream& operator<<(std::ostream& os, const glm::mat3& mat)
	{
		return os << "\n{" << mat[0][0] << "\t" << mat[0][1] << "\t" << mat[0][2] << "\n"
			<< mat[1][0] << "\t" << mat[1][1] << "\t" << mat[1][2] << "\n"
			<< mat[2][0] << "\t" << mat[2][1] << "\t" << mat[2][2] << "}";
	}

	inline std::ostream& operator<<(std::ostream& os, const glm::mat4& mat)
	{
		return os << "\n{" << mat[0][0] << "\t" << mat[0][1] << "\t" << mat[0][2] << "\t" << mat[0][3] << "\n"
			<< mat[1][0] << "\t" << mat[1][1] << "\t" << mat[1][2] << "\t" << mat[1][3] << "\n"
			<< mat[2][0] << "\t" << mat[2][1] << "\t" << mat[2][2] << "\t" << mat[2][3] << "\n"
			<< mat[3][0] << "\t" << mat[3][1] << "\t" << mat[3][2] << "\t" << mat[3][3] << "}";
	}
}
