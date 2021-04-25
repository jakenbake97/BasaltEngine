#pragma once
#include <exception>
#include <string>

namespace Basalt
{
	class Exception : public std::exception
	{
	protected:
		mutable std::string whatBuffer;
	private:
		int line;
		std::string file;
	public:
		Exception(int line, std::string file);
		const char* what() const override;
		virtual std::string GetType() const;
		int GetLine() const;
		std::string GetFile() const;
		std::string GetOriginString() const;
	};
}
