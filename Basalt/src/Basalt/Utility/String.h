#pragma once

#include <string>
#include "Basalt/Core.h"

// This excludes all warnings raised inside External headers
#include <CodeAnalysis\Warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning( pop )


namespace Basalt
{
	class String
	{
	private:
		std::wstring data;
	public:
		String() = default;

		String(const wchar_t* string)
			: data(string)
		{
		}

		String(std::wstring& string)
			: data(string)
		{
		}

		String(const char* string)
		{
			data = Wide(string);
		}

		String(const std::string& string)
		{
			data = Wide(string);
		}

		String(const int i)
		{
			data = std::to_wstring(i);
		}

		String(const unsigned int u)
		{
			data = std::to_wstring(u);
		}

		String(const float f)
		{
			data = std::to_wstring(f);
		}

		String(const double d)
		{
			data = std::to_wstring(d);
		}

		String operator+(const String& object) const // Concatenation
		{
			std::wstring temp = data + object.data;
			return String(temp);
		}

		String& operator+=(const String& object)
		{
			data += object.Get();
			return *this;
		}

		String& operator+=(const std::wstring& object)
		{
			data += object;
			return *this;
		}

		String& operator+=(const std::string& object)
		{
			data += Wide(object);
			return *this;
		}

		String& operator+=(const wchar_t* object)
		{
			data += object;
			return *this;
		}

		String& operator+=(const char* object)
		{
			data += Wide(object);
			return *this;
		}

		String operator+(const int i)
		{
			String temp(data);
			return temp += std::to_wstring(i);
		}

		String& operator+=(const int i)
		{
			data += std::to_wstring(i);
			return *this;
		}

		String operator+(const unsigned int u)
		{
			String temp(data);
			return temp += std::to_wstring(u);
		}

		String& operator+=(const unsigned int u)
		{
			data += std::to_wstring(u);
			return *this;
		}

		String operator+(const float f)
		{
			String temp(data);
			return temp += std::to_wstring(f);
		}

		String& operator+=(const float f)
		{
			data += std::to_wstring(f);
			return *this;
		}

		String operator+(const double d)
		{
			String temp(data);
			return temp += std::to_wstring(d);
		}

		String& operator+=(const double d)
		{
			data += std::to_wstring(d);
			return *this;
		}

		operator std::string() const
		{
			return Narrow();
		}

		explicit operator std::wstring() const
		{
			return data;
		}

		unsigned int Size() const
		{
			return (unsigned int)data.size();
		}

		const wchar_t* CStr() const
		{
			return data.c_str();
		}

		std::wstring Get() const
		{
			return data;
		}

		std::string Narrow() const
		{
			std::string narrow;
			narrow.resize(data.size());

			WideCharToMultiByte(CP_ACP, 0, data.c_str(), (int)data.size(), narrow.data(), (int)data.size(), nullptr, nullptr);

			return narrow;
		}

		void PushBack(char character)
		{
			wchar_t wideChar;
			mbtowc(&wideChar, &character, 1);

			data.push_back(wideChar);
		}

		void PushBack(const wchar_t character)
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
			return os << s.Narrow();
		}

	private:
		static std::wstring Wide(const std::string& inString)
		{
			std::wstring wide;
			wide.resize(inString.size());

			MultiByteToWideChar(CP_ACP, 0, inString.c_str(), (int)inString.size(), wide.data(), (int)inString.size());

			return wide;
		}
	};

	inline String operator+(const char* lhs, String& rhs)
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
