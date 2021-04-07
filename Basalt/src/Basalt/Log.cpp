#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Basalt
{
	std::shared_ptr<spdlog::logger> Log::coreLogger;
	std::shared_ptr<spdlog::logger> Log::clientLogger;
	
	void Log::Init(const std::string& clientName)
	{
		// %^ starts color range
		// %T prints the time
		// %n prints the name of the logger
		// %v prints the actual message
		// %$ ends the color range
		spdlog::set_pattern("%^[%T] %n: %v%$");

		coreLogger = spdlog::stdout_color_mt("BASALT");
		coreLogger->set_level(spdlog::level::trace);
		
		clientLogger = spdlog::stdout_color_mt(clientName);
		clientLogger->set_level(spdlog::level::trace);
	}
}
