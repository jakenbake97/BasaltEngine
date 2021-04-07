#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"

namespace Basalt
{
	class BASALT_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }
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

template <typename T>
constexpr void BAS_LOG(Basalt::ELogger logger, Basalt::ELogSeverity severity, const T& message)
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