#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "Utility/String.h"

namespace Basalt
{
	class BASALT_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;	
	public:
		static void Init(const class String& clientName);

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }
	};

	enum class ELogger
	{
		Core,
		Client
	};

	enum class ELogSeverity
	{
		Trace,
		Info,
		Warn,
		Error,
	};
}

#ifndef BE_DIST
// If non-distribution build
template <typename T, typename... Types>
void BE_LOG(const Basalt::ELogger logger, const Basalt::ELogSeverity severity, T& message, Types... additionalMessages)
{
	
	std::shared_ptr<spdlog::logger> log;
	if (logger == Basalt::ELogger::Core)
	{
		log = Basalt::Log::GetCoreLogger();
	}
	else
	{
		log = Basalt::Log::GetClientLogger();
	}
	
	switch (severity)
	{
	case Basalt::ELogSeverity::Trace:
		log->trace(message, additionalMessages...);
		break;
	case Basalt::ELogSeverity::Info:
		log->info(message, additionalMessages...);
		break;
	case Basalt::ELogSeverity::Warn:
		log->warn(message, additionalMessages...);
		break;
	case Basalt::ELogSeverity::Error:
		log->error(message, additionalMessages...);
		break;
	}
}
#endif

#ifdef BE_DIST
// If distribution build
template <typename T, typename... Types>
void BE_LOG(const Basalt::ELogger logger, const Basalt::ELogSeverity severity, T message, Types... additionalMessage) {};
#endif