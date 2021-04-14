#pragma once
#include <string>
#include <Windows.h>

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

		String operator+(const String& object) const // Concatenation
		{
			std::wstring temp = data + object.data;
			return String(temp);
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
			
			WideCharToMultiByte(CP_UTF8, 0, data.c_str(), data.size(), narrow.data(), data.size(), nullptr, nullptr);

			return narrow;
		}

	private:
		static std::wstring Wide(const std::string& inString)
		{
			std::wstring wide;
			wide.resize(inString.size());

			MultiByteToWideChar(CP_UTF8, 0, inString.c_str(), inString.size(), wide.data(), inString.size());

			return wide;
		}
	};
}