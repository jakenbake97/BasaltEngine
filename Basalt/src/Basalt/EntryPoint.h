#pragma once

#include "BEpch.h"
#include "Application.h"
#include "Exception.h"
#include "IWindow.h"

#ifdef BE_PLATFORM_WINDOWS

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Basalt::Log::InitCoreLog();
	try
	{
		// Initialize engine application
		auto app = Basalt::CreateApplication();

		// Initialize the logger
		Basalt::Log::InitClientLog(app->GetAppName());

		app->Update();
		
		return app->GetExitCode();
	}

	// Catch issues in creating application before the logger is created
	catch (const Basalt::Exception& e)
	{
		BE_ERROR(e.GetException());
	}
	catch (const std::exception& e)
	{
		BE_ERROR(e.what());
	}
	catch (...)
	{
		BE_ERROR("Unknown Exception | No exception details available");
	}
	system("pause");
	return -1;
}

#endif
