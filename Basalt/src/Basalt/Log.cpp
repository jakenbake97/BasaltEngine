#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "Utility/String.h"

namespace Basalt
{
	BASALT_API std::shared_ptr<spdlog::logger> Log::coreLogger;
	BASALT_API std::shared_ptr<spdlog::logger> Log::clientLogger;
	
	void Log::Init(const String& clientName)
	{
		// Setup console for winMain
		AllocConsole();
		
		// %^ starts color range
		// %T prints the time
		// %n prints the name of the logger
		// %v prints the actual message
		// %$ ends the color range
		spdlog::set_pattern("%^[%T] %n: %v%$");

		coreLogger = spdlog::stdout_color_mt("BASALT");
		coreLogger->set_level(spdlog::level::trace);

		std::wstring test(L"SANDBOX");
		
		clientLogger = spdlog::stdout_color_mt(clientName.Narrow());
		clientLogger->set_level(spdlog::level::trace);
	}
}
