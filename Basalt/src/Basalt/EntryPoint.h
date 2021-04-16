#pragma once

#include <Windows.h>

#include "Platform/WindowsMessageMap.h"
#include "Utility/String.h"

#ifdef BE_PLATFORM_WINDOWS

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static Basalt::Platform::WindowsMessageMap msgMap;
	BE_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Trace, msgMap(msg, lParam, wParam).Narrow());
	
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wParam == 'F')
		{
			SetWindowText(hWnd, L"Key is down!");
		}
		break;
	case WM_KEYUP:
		SetWindowText(hWnd, L"No key pressed");
		break;
	}
	
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// Initialize engine application
	auto* app = Basalt::CreateApplication();

	// Initialize the logger
	Basalt::Log::Init(app->GetAppName());
	
	const Basalt::String className(L"Basalt Engine");

	// Register Window Class
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
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
	                                      WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
	                                      500, 200, 1600, 900,
	                                      nullptr, nullptr, hInstance, nullptr);

	ShowWindow(wndHandle, SW_SHOW);
	BE_LOG(Basalt::ELogger::Core, Basalt::ELogSeverity::Trace, "1600x900 window successfully created");

	const int exitCode = app->Run();
	delete app;

	return exitCode;
}

#endif
