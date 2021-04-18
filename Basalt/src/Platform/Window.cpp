#include "Window.h"
#include "../Basalt/Utility/String.h"
#include "../Basalt/Log.h"

namespace Basalt::Platform
{
	Window::WindowClass Window::WindowClass::wndClass;

	Window::WindowClass::WindowClass()
		: hInst(GetModuleHandle(nullptr))
	{
		// Register Window Class
		WNDCLASSEX wc = {};
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = HandleMsgSetup;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetInstance();
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = GetName();
		wc.hIconSm = nullptr;

		RegisterClassEx(&wc);
	}

	Window::WindowClass::~WindowClass()
	{
		UnregisterClass(GetName(), GetInstance());
	}

	const wchar_t* Window::WindowClass::GetName()
	{
		return L"Basalt Engine";
	}

	HINSTANCE Window::WindowClass::GetInstance()
	{
		return wndClass.hInst;
	}

	Window::Window(int width, int height, const String& name)
	{
		RECT windowRegion;
		windowRegion.left = 100;
		windowRegion.right = width + windowRegion.left;
		windowRegion.top = 100;
		windowRegion.bottom = height + windowRegion.top;

		AdjustWindowRect(&windowRegion, WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU, false);

		handle = CreateWindow(WindowClass::GetName(), name.CStr(),
		                      WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
		                      windowRegion.right - windowRegion.left, windowRegion.bottom - windowRegion.top, nullptr,
		                      nullptr,
		                      WindowClass::GetInstance(), this
		);

		ShowWindow(handle, SW_SHOWDEFAULT);

		BE_LOG(ELogger::Core, ELogSeverity::Trace, "{0} x {1} Window Successfully Created!", width, height);
	}

	Window::~Window()
	{
		DestroyWindow(handle);
	}

	LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// use the create parameter passed in from CreateWindow() to store window class pointer
		if (msg == WM_NCCREATE)
		{
			// extract ptr to window class from creation data
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			Window* const pWindow = static_cast<Window*>(pCreate->lpCreateParams);
			// set WinAPI-managed user data to store ptr to window class
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
			// set message proc to normal (non-setup) handler now that setup is finished
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgAdapter));
			// forward message to window class message handler
			return pWindow->HandleMsg(hWnd, msg, wParam, lParam);
		}
		// if a message comes before the WM_NCCREATE message, handle with the default handler
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	LRESULT WINAPI Window::HandleMsgAdapter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// retrieve ptr to window class
		Window* const pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		// forward message to the window class message handler
		return pWindow->HandleMsg(hWnd, msg, wParam, lParam);
	}

	LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}
