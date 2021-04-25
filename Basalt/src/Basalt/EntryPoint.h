#pragma once

#include "../Platform/Window.h"
#include "Application.h"
#include "Utility/String.h"
#include "Log.h"

#ifdef BE_PLATFORM_WINDOWS

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Basalt::Log::InitCoreLog();
	try
	{
		// Initialize engine application
		auto* app = Basalt::CreateApplication();

		// Initialize the logger
		Basalt::Log::InitClientLog(app->GetAppName());

		const Basalt::String className(L"Basalt Engine");
		
		BE_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Warn, "Class Name: {0}, App Name: {1}",className, app->GetAppName());
	
		const Basalt::String windowName = className + L" - " + app->GetAppName();

		// Create window instance
		Basalt::Platform::Window window(1600, 900, windowName);

		const int exitCode = app->Run();
		delete app;

		return exitCode;
	}

	// Catch issues in creating application before the logger is created
	catch (const Basalt::Exception& e)
	{
		BE_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Error, e.GetException());
	}
	catch (const std::exception& e)
	{
		BE_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Error, e.what());
	}
	catch (...)
	{
		BE_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Error, "Unknown Exception; No exception details available");
	}
	system("pause");
	return -1;
}

#endif
