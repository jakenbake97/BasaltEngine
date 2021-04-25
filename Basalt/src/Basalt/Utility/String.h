#pragma once

#include "../../Platform/WindowsIncludes.h"
#include <string>
#include "../Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Basalt
{
	class BASALT_API String
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
		
		String& operator+=(std::wstring& object)
		{
			data += object;
			return *this;
		}

		String& operator+=(std::string& object)
		{
			data += Wide(object);
			return *this;
		}

		String& operator+=(wchar_t* object)
		{
			data += object;
			return *this;
		}

		String& operator+=(char* object)
		{
			data += Wide(object);
			return *this;
		}

		unsigned int Size() const
		{
			return data.size();
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
			
			WideCharToMultiByte(CP_ACP, 0, data.c_str(), data.size(), narrow.data(), data.size(), nullptr, nullptr);

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

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const String& s)
		{
			return os << s.Narrow();
		}

	private:
		static std::wstring Wide(const std::string& inString)
		{
			std::wstring wide;
			wide.resize(inString.size());

			MultiByteToWideChar(CP_ACP, 0, inString.c_str(), inString.size(), wide.data(), inString.size());

			return wide;
		}
	};
}