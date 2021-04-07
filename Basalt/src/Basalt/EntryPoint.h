#pragma once

#ifdef BAS_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
	Basalt::Log::Init();
	BAS_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Warn, "Initialized Logger");
	BAS_LOG(Basalt::ELogger::Client, Basalt::ELogSeverity::Info, "Initialized Logger");
	
	auto* app = Basalt::CreateApplication();
	app->Run();
	delete app;
}

#endif