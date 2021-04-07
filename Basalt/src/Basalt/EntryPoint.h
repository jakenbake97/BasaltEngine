#pragma once

#ifdef BE_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
	auto* app = Basalt::CreateApplication();
	
	Basalt::Log::Init(app->GetAppName());
	BE_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Trace, "Initialized Logger");
	BE_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Info, "Initialized Logger");
	BE_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Warn, "Initialized Logger");
	BE_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Error, "Initialized Logger\n");
	
	BE_LOG(Basalt::ELogger::Client, Basalt::ELogSeverity::Trace, "Initialized Logger");
	BE_LOG(Basalt::ELogger::Client, Basalt::ELogSeverity::Info, "Initialized Logger");
	BE_LOG(Basalt::ELogger::Client, Basalt::ELogSeverity::Warn, "Initialized Logger");
	BE_LOG(Basalt::ELogger::Client, Basalt::ELogSeverity::Error, "Initialized Logger");
	
	app->Run();
	delete app;

	return EXIT_SUCCESS;
}

#endif