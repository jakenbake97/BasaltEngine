#pragma once

#include <memory>
#include "Core.h"
#include "Utility/String.h"
#include "spdlog/spdlog.h"

namespace Basalt
{
	class BASALT_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;	
	public:
		static void Init(const class String& clientName);
		static void InitCoreLog();
		static void InitClientLog(const class String& clientName);

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
void BE_LOG(const Basalt::ELogger logger, const Basalt::ELogSeverity severity, T formatString, Types... additionalArguments)
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
		log->trace(formatString, additionalArguments...);
		break;
	case Basalt::ELogSeverity::Info:
		log->info(formatString, additionalArguments...);
		break;
	case Basalt::ELogSeverity::Warn:
		log->warn(formatString, additionalArguments...);
		break;
	case Basalt::ELogSeverity::Error:
		log->error(formatString, additionalArguments...);
		break;
	}
}
#endif

#ifdef BE_DIST
// If distribution build
template <typename T, typename... Types>
void BE_LOG(const Basalt::ELogger logger, const Basalt::ELogSeverity severity, T formatString, Types... additionalArguments) {};
#endif