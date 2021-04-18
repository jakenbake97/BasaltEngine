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
		wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
		wc.lpfnWndProc = HandleMsgSetup;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetInstance();
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
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

	Window::Window(const int width, const int height, const String& name)
		: width(width), height(height)
	{
		RECT windowRect;
		windowRect.left = 0;
		windowRect.right = width;
		windowRect.top = 0;
		windowRect.bottom = height;

		const auto styles = WS_OVERLAPPEDWINDOW;
		
		AdjustWindowRect(&windowRect, styles, false);

		handle = CreateWindow(WindowClass::GetName(), name.CStr(),
		                      styles, 300, 300,
		                      windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr,
		                      nullptr,
		                      WindowClass::GetInstance(), this
		);

		if (!handle)
		{
			BE_LOG(ELogger::Core, ELogSeverity::Error, "Failed to create window!");
			PostQuitMessage(-1);
			return;
		}

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

	void Window::HandleWindowResize(HWND hWnd, UINT width, UINT height) const
	{
		RECT clientRect, windowRect;
		POINT pointDiff;
		GetClientRect(hWnd, &clientRect);
		GetWindowRect(hWnd, &windowRect);
		pointDiff.x = (windowRect.right - windowRect.left) - clientRect.right;
		pointDiff.y = (windowRect.bottom - windowRect.top) - clientRect.bottom;
		MoveWindow(hWnd, windowRect.left, windowRect.top, width + pointDiff.x, height + pointDiff.y, TRUE);
	}

	LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) const
	{
		switch (msg)
		{
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		case WM_SIZE:
			HandleWindowResize(hWnd, LOWORD(lParam), HIWORD(lParam));
			return 0;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}
