#include "BEpch.h"
#include "Log.h"

#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include "spdlog/sinks/stdout_color_sinks.h"
#pragma warning( pop )

namespace Basalt
{
	std::shared_ptr<spdlog::logger> Log::coreLogger = nullptr;
	std::shared_ptr<spdlog::logger> Log::clientLogger = nullptr;
	
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
		clientLogger = spdlog::stdout_color_mt(clientName);
		clientLogger->set_level(spdlog::level::trace);
	}
}
