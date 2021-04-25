#include "Exception.h"

#include <utility>

Basalt::Exception::Exception(const int line, std::string file)
	:line(line), file(std::move(file))
{
}

const char* Basalt::Exception::what() const
{
	whatBuffer = GetType() + "\n" + GetOriginString();
	return whatBuffer.c_str();
}

std::string Basalt::Exception::GetType() const
{
	return { "Basalt Exception" };
}

int Basalt::Exception::GetLine() const
{
	return line;
}

std::string Basalt::Exception::GetFile() const
{
	return file;
}

std::string Basalt::Exception::GetOriginString() const
{
	return "[File] " + file + "\n" + "[Line] " + std::to_string(line);
}
