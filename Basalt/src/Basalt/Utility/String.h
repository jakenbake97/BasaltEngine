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
	class String
	{
	public:
		String() = default;

		String(const wchar_t* string)
		{
			data = Narrow(string);
		}

		String(const std::wstring& string)
		{
			data = Narrow(string);
		}

		String(const char* string)
			: data(string)
		{
		}

		String(std::string string)
			: data(std::move(string))
		{
		}

		String(const int32 i)
		{
			data = std::to_string(i);
		}

		String(const uint32 u)
		{
			data = std::to_string(u);
		}

		String(const float f)
		{
			data = std::to_string(f);
		}

		String(const double d)
		{
			data = std::to_string(d);
		}

		String operator+(const String& object) const // Concatenation
		{
			const std::string temp = data + object.data;
			return String(temp);
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

		uint32 Size() const
		{
			return (uint32)data.size();
		}

		const char* CStr() const
		{
			return data.c_str();
		}

		std::string Get() const
		{
			return data;
		}

		void PushBack(const wchar_t character)
		{
			data += Narrow(std::wstring(&character));
		}

		void PushBack(const char character)
		{
			data.push_back(character);
		}

		bool Empty() const
		{
			return data.empty();
		}

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
