#pragma once

#include <exception>

namespace Basalt
{
	class Exception : public std::exception
	{
	public:
		Exception(int line, String file);
		virtual String GetException() const;
		virtual String GetType() const;
		int GetLine() const;
		String GetFile() const;
		String GetOriginString() const;
	private:
		const char* what() const override;

	protected:
		mutable std::string whatBuffer;
	private:
		int line;
		String file;
	};
}
