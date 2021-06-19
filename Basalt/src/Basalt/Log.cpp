#include "BEpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Basalt
{
	BASALT_API std::shared_ptr<spdlog::logger> Log::coreLogger = nullptr;
	BASALT_API std::shared_ptr<spdlog::logger> Log::clientLogger = nullptr;
	
	void Log::Init(const String& clientName)
	{
		if (!coreLogger)
		{
			InitCoreLog();
		}
		if (!clientLogger)
		{
			InitClientLog(clientName);
		}
	}

	void Log::InitCoreLog()
	{
		// Setup console for winMain
		AllocConsole();
		SetConsoleTitle(L"Basalt Engine");

		// %^ starts color range
		// %T prints the time
		// %n prints the name of the logger
		// %v prints the actual message
		// %$ ends the color range
		spdlog::set_pattern("%^[%T] %n: %v%$");

		coreLogger = spdlog::stdout_color_mt("BASALT");
		coreLogger->set_level(spdlog::level::trace);
	}

	void Log::InitClientLog(const String& clientName)
	{
		if (!coreLogger)
		{
			InitCoreLog();
		}
		clientLogger = spdlog::stdout_color_mt(clientName.Narrow());
		clientLogger->set_level(spdlog::level::trace);
	}
}
