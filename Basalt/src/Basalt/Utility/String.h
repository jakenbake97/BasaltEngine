#pragma once
#include <string>
#include <utility>

#ifdef BE_PLATFORM_WINDOWS
#include <atlstr.h>
#endif


// This excludes all warnings raised inside External headers
#include <CodeAnalysis\Warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include "Math.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning( pop )


namespace Basalt
{
	/// <summary>
	/// Basalt's utility string class serves as an extension to std::string
	/// </summary>
	class String
	{
	public:
		String() = default;

		/// <summary>
		/// Constructs a string from a wide char pointer
		/// </summary>
		/// <param name="string">The input wide string to create the Basalt string from</param>
		String(const wchar_t* string)
		{
			data = Narrow(string);
		}

		/// <summary>
		/// Constructs a string from a wide string
		/// </summary>
		/// <param name="string">The input wide string to create the Basalt string from</param>
		String(const std::wstring& string)
		{
			data = Narrow(string);
		}

		/// <summary>
		/// Constructs a string from a char pointer
		/// </summary>
		/// <param name="string">The input string to create the Basalt string from</param>
		String(const char* string)
			: data(string)
		{
		}

		/// <summary>
		/// Constructs a string from an std::string
		/// </summary>
		/// <param name="string">The input string to create the Basalt string from</param>
		String(std::string string)
			: data(std::move(string))
		{
		}

		/// <summary>
		/// Constructs a string from a 32-bit integer
		/// </summary>
		/// <param name="i">The integer to create the Basalt string from</param>
		String(const int32 i)
		{
			data = std::to_string(i);
		}

		/// <summary>
		/// Constructs a string from a 32-bit unsigned integer
		/// </summary>
		/// <param name="u">The unsigned integer to create the Basalt string from</param>
		String(const uint32 u)
		{
			data = std::to_string(u);
		}

		/// <summary>
		/// Constructs a string from a floating point number
		/// </summary>
		/// <param name="f">The float to create the Basalt string from</param>
		String(const float f)
		{
			data = std::to_string(f);
		}

		/// <summary>
		/// Constructs a string from a double precision number
		/// </summary>
		/// <param name="d">The double to create the Basalt string from</param>
		String(const double d)
		{
			data = std::to_string(d);
		}

		String operator+(const String& object) const // Concatenation
		{
			const std::string temp = data + object.data;
			return {temp};
		}

		String& operator+=(const String& object)
		{
			data += object.Get();
			return *this;
		}

		String& operator+=(const std::string& object)
		{
			data += object;
			return *this;
		}

		String& operator+=(const std::wstring& object)
		{
			data += Narrow(object);
			return *this;
		}

		String& operator+=(const char* object)
		{
			data += object;
			return *this;
		}

		String& operator+=(const wchar_t* object)
		{
			data += Narrow(object);
			return *this;
		}

		String operator+(const int i) const
		{
			String temp(data);
			return temp += std::to_string(i);
		}

		String& operator+=(const int i)
		{
			data += std::to_string(i);
			return *this;
		}

		String operator+(const uint32 u) const
		{
			String temp(data);
			return temp += std::to_string(u);
		}

		String& operator+=(const uint32 u)
		{
			data += std::to_string(u);
			return *this;
		}

		String operator+(const float f) const
		{
			String temp(data);
			return temp += std::to_string(f);
		}

		String& operator+=(const float f)
		{
			data += std::to_string(f);
			return *this;
		}

		String operator+(const double d) const
		{
			String temp(data);
			return temp += std::to_string(d);
		}

		String& operator+=(const double d)
		{
			data += std::to_string(d);
			return *this;
		}

		operator std::string() const
		{
			return data;
		}

		explicit operator std::wstring() const
		{
			return Wide(data);
		}

		/// <summary>
		/// Returns the size (number of characters) of the underlying string
		/// </summary>
		/// <returns>The number of characters in the string</returns>
		uint32 Size() const
		{
			return (uint32)data.size();
		}

		/// <summary>
		/// Converts the string into a C style string
		/// </summary>
		/// <returns>The string formatted as a const char pointer</returns>
		const char* CStr() const
		{
			return data.c_str();
		}

		/// <summary>
		/// Returns the string as an std::string
		/// </summary>
		/// <returns>The underlying std::string</returns>
		std::string Get() const
		{
			return data;
		}

		/// <summary>
		/// Appends a wide character to the string
		/// </summary>
		/// <param name="character">The wide character to append to the current string</param>
		void PushBack(const wchar_t character)
		{
			data += Narrow(std::wstring(&character));
		}

		/// <summary>
		/// Appends a character to the string
		/// </summary>
		/// <param name="character">The character to append to the current string</param>
		void PushBack(const char character)
		{
			data.push_back(character);
		}

		/// <summary>
		/// Returns a bool indicating if there are any characters in the string
		/// </summary>
		/// <returns>true if there are no characters in the string, false if there is one or more characters in the string</returns>
		bool Empty() const
		{
			return data.empty();
		}

		/// <summary>
		/// Erases the last character of the string, reducing the length by one
		/// </summary>
		void PopBack()
		{
			data.pop_back();
		}

		friend std::ostream& operator<<(std::ostream& os, const String& s)
		{
			return os << s.data;
		}

	private:
		static std::string Narrow(const std::wstring& inString)
		{
			std::string narrow;
			narrow.resize(inString.size());

			WideCharToMultiByte(CP_UTF8, 0, inString.c_str(), (int)inString.size(), narrow.data(), (int)inString.size(), nullptr, nullptr);

			return narrow;
		}

		static std::wstring Wide(const std::string& inString)
		{
			std::wstring wide;
			wide.resize(inString.size());

			MultiByteToWideChar(CP_UTF8, 0, inString.c_str(), (int)inString.size(), wide.data(), (int)inString.size());

			return wide;
		}

		std::string data;
	};

	inline String operator+(const char* lhs, const String& rhs)
	{
		const String temp(lhs);
		return temp + rhs;
	}

	inline String operator+(const wchar_t* lhs, const String& rhs)
	{
		const String temp(lhs);
		return temp + rhs;
	}
}
