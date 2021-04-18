#pragma once

#include "../Platform/Window.h"
#include "Application.h"
#include "Log.h"
#include "Utility/String.h"

#ifdef BE_PLATFORM_WINDOWS

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// Initialize engine application
	auto* app = Basalt::CreateApplication();

	// Initialize the logger
	Basalt::Log::Init(app->GetAppName());

	const Basalt::String className(L"Basalt Engine");

	
	const Basalt::String windowName = className + L" - " + app->GetAppName();

	// Create window instance
	Basalt::Platform::Window window(1600, 900, windowName);

	const int exitCode = app->Run();
	delete app;

	return exitCode;
}

#endif
