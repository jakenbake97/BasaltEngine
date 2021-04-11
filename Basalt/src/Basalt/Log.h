#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"

namespace Basalt
{
	class BASALT_API Log
	{
	public:
		static void Init(const std::string& clientName);

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
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
template <typename T>
constexpr void BE_LOG(const Basalt::ELogger logger, const Basalt::ELogSeverity severity, const T& message)
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
		log->trace(message);
		break;
	case Basalt::ELogSeverity::Info:
		log->info(message);
		break;
	case Basalt::ELogSeverity::Warn:
		log->warn(message);
		break;
	case Basalt::ELogSeverity::Error:
		log->error(message);
		break;
	}
}
#endif

#ifdef BE_DIST
// If distribution build
 template <typename T>
 constexpr void BE_LOG(const Basalt::ELogger logger, const Basalt::ELogSeverity severity, const T& message) {};
#endif