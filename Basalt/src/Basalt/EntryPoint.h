#pragma once

#include <Windows.h>

#include "Utility/String.h"

#ifdef BE_PLATFORM_WINDOWS

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// Initialize engine application
	auto* app = Basalt::CreateApplication();

	// Initialize the logger
	Basalt::Log::Init(app->GetAppName());
	
	const Basalt::String className(L"Basalt Engine");

	BE_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Trace, "Initialized Trace");
	BE_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Info, "Initialized Info");
	BE_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Warn, "Initialized Warn");
	BE_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Error, "Initialized Error\n");

	BE_LOG(Basalt::ELogger::Client, Basalt::ELogSeverity::Trace, "Initialized Trace");
	BE_LOG(Basalt::ELogger::Client, Basalt::ELogSeverity::Info, "Initialized Info");
	BE_LOG(Basalt::ELogger::Client, Basalt::ELogSeverity::Warn, "Initialized Warn");
	BE_LOG(Basalt::ELogger::Client, Basalt::ELogSeverity::Error, "Initialized Error\n");

	// Register Window Class
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = className.CStr();
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);
	
	// Create window instance
	const Basalt::String windowName = className + L" - " + app->GetAppName();
	
	HWND wndHandle = CreateWindowEx(0, className.CStr(), windowName.CStr(),
	                                      WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
	                                      500, 200, 1600, 900,
	                                      nullptr, nullptr, hInstance, nullptr);

	ShowWindow(wndHandle, SW_SHOW);

	app->Run();
	delete app;

	return EXIT_SUCCESS;
}

#endif
