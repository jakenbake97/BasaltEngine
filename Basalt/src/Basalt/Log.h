#pragma once

#include "Core.h"
#include "Utility/String.h"

// This excludes all warnings raised inside External headers
#pragma warning(push)
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)

namespace Basalt
{
	class Log
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

// If non-distribution build
#ifndef BE_DIST

template <typename T, typename... Types>
void BE_LOG(const Basalt::ELogger logger, const Basalt::ELogSeverity severity, T& formatString, Types&... additionalArguments)
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

template <typename T, typename... Types>
void BE_CORE_LOG(const Basalt::ELogSeverity severity, const T& formatString, const Types&... additionalArguments)
{
	BE_LOG(Basalt::ELogger::Core, severity, formatString, additionalArguments...);
}

template <typename T, typename... Types>
void BE_CLIENT_LOG(const Basalt::ELogSeverity severity, const T& formatString, const Types&... additionalArguments)
{
	BE_LOG(Basalt::ELogger::Client, severity, formatString, additionalArguments...);
}

#ifdef BE_STATIC_LIB
template <typename T, typename... Types>
void BE_TRACE(const T& formatString, const Types&... additionalArguments)
{
	BE_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Trace, formatString, additionalArguments...);
}

template <typename T, typename... Types>
void BE_INFO(const T& formatString, const Types&... additionalArguments)
{
	BE_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Info, formatString, additionalArguments...);
}

template <typename T, typename... Types>
void BE_WARN(const T& formatString, const Types&... additionalArguments)
{
	BE_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Warn, formatString, additionalArguments...);
}

template <typename T, typename... Types>
void BE_ERROR(const T& formatString, const Types&... additionalArguments)
{
	BE_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Error, formatString, additionalArguments...);
}

#else
template <typename T, typename... Types>
void BE_TRACE(const T& formatString, const Types&... additionalArguments)
{
	BE_LOG(Basalt::ELogger::Client, Basalt::ELogSeverity::Trace, formatString, additionalArguments...);
}

template <typename T, typename... Types>
void BE_INFO(const T& formatString, const Types&... additionalArguments)
{
	BE_LOG(Basalt::ELogger::Client, Basalt::ELogSeverity::Info, formatString, additionalArguments...);
}

template <typename T, typename... Types>
void BE_WARN(const T& formatString, const Types&... additionalArguments)
{
	BE_LOG(Basalt::ELogger::Client, Basalt::ELogSeverity::Warn, formatString, additionalArguments...);
}

template <typename T, typename... Types>
void BE_ERROR(const T& formatString, const Types&... additionalArguments)
{
	BE_LOG(Basalt::ELogger::Client, Basalt::ELogSeverity::Error, formatString, additionalArguments...);
}
#endif
#endif

#ifdef BE_DIST
// If distribution build
template <typename T, typename... Types>
void BE_LOG(const Basalt::ELogger logger, const Basalt::ELogSeverity severity, T formatString, Types... additionalArguments) {}

template <typename T, typename... Types>
void BE_CORE_LOG(const Basalt::ELogSeverity severity, T formatString, Types... additionalArguments) {}

template <typename T, typename... Types>
void BE_CLIENT_LOG(const Basalt::ELogSeverity severity, T formatString, Types... additionalArguments) {}

template <typename T, typename... Types>
void BE_TRACE(T formatString, Types... additionalArguments){}

template <typename T, typename... Types>
void BE_INFO(T formatString, Types... additionalArguments){}

template <typename T, typename... Types>
void BE_WARN(T formatString, Types... additionalArguments){}

template <typename T, typename... Types>
void BE_ERROR(T formatString, Types... additionalArguments) {}
#endif