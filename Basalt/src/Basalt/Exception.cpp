#include "BEpch.h"
#include "Exception.h"

namespace Basalt
{
	Exception::Exception(const int line, String file)
		: line(line), file(std::move(file))
	{
	}

	String Exception::GetException() const
	{
		return String(what());
	}

	const char* Exception::what() const
	{
		whatBuffer = (GetType() + "\n" + GetOriginString());
		return whatBuffer.c_str();
	}

	String Exception::GetType() const
	{
		return {"Generic Basalt Exception"};
	}

	int Exception::GetLine() const
	{
		return line;
	}

	String Exception::GetFile() const
	{
		return file;
	}

	String Exception::GetOriginString() const
	{
		return  "[File] " + file + "\n[Line] " + line;
	}
}
