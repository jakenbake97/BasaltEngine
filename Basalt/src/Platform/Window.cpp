#include "BEpch.h"
#include "Window.h"

#include <utility>

#include "WindowsInput.h"
#include "Basalt/Application.h"
#include "Basalt/IInput.h"
#include "Basalt/Utility/String.h"
#include "Basalt/Log.h"
#include "Basalt/Events/WindowEvent.h"
#include "Basalt/Events/KeyboardEvent.h"

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

		if (!AdjustWindowRect(&windowRect, styles, false))
		{
			throw BE_WND_LAST_EXCEPT();
		}

		handle = CreateWindow(WindowClass::GetName(), name.CStr(),
		                      styles, 300, 300,
		                      windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
		                      nullptr, nullptr,
		                      WindowClass::GetInstance(), this
		);

		if (!handle)
		{
			throw BE_WND_LAST_EXCEPT();
		}

		ShowWindow(handle, SW_SHOWDEFAULT);

		BE_LOG(ELogger::Core, ELogSeverity::Trace, "{0} x {1} Window Successfully Created!", width, height);
	}

	Window::~Window()
	{
		DestroyWindow(handle);
	}

	Window::WindowException::WindowException(const int line, String file, const HRESULT hr)
		: Exception(line, std::move(file)), hr(hr)
	{
	}

	String Window::WindowException::GetException() const
	{
		return GetType()
			+ L"\n[Error Code] " + GetErrorCode()
			+ L"\n[Description] " + GetErrorString()
			+ GetOriginString();
	}

	String Window::WindowException::GetType() const
	{
		return "Basalt Window Exception";
	}

	String Window::WindowException::TranslateErrorCode(const HRESULT hr)
	{
		wchar_t* msgBuf = nullptr;

		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		                  nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		                  reinterpret_cast<LPWSTR>(&msgBuf), 0, nullptr) == 0)
		{
			return L"Unidentified error code";
		}
		String errorString = msgBuf;
		LocalFree(msgBuf);
		return errorString;
	}

	HRESULT Window::WindowException::GetErrorCode() const
	{
		return hr;
	}

	String Window::WindowException::GetErrorString() const
	{
		return TranslateErrorCode(hr);
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
		auto* const pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		// forward message to the window class message handler
		return pWindow->HandleMsg(hWnd, msg, wParam, lParam);
	}

	void Window::HandleWindowResize(HWND hWnd, UINT width, UINT height)
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
			// -- Window Messages --
		case WM_CLOSE:
			{
				PostQuitMessage(0);
				const auto event = std::make_shared<WindowCloseEvent>(0);
				Application::OnEvent(event);

				break;
			}
		case WM_SIZE:
			{
				HandleWindowResize(hWnd, LOWORD(lParam), HIWORD(lParam));
				const auto event = std::make_shared<WindowResizeEvent>(LOWORD(lParam), HIWORD(lParam));
				Application::OnEvent(event);

				break;
			}
		case WM_KILLFOCUS:
			{
				IInput::ClearState();
				const auto event = std::make_shared<WindowLostFocusEvent>();
				Application::OnEvent(event);
				break;
			}
			// -- Keyboard Messages --
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			{
				if (!(lParam & 0x40000000))
				{
					const WPARAM virtualCode = MapLeftRightKeys(wParam, lParam);
					const KeyCode basaltCode = Key::ConvertToBasaltKeyCode.at(static_cast<unsigned char>(virtualCode));
					IInput::OnKeyDown(basaltCode);
				}
				break;
			}
		case WM_SYSKEYUP:
		case WM_KEYUP:
			{
				const WPARAM virtualCode = MapLeftRightKeys(wParam, lParam);
				const KeyCode basaltCode = Key::ConvertToBasaltKeyCode.at(static_cast<unsigned char>(virtualCode));
				IInput::OnKeyUp(basaltCode);

				break;
			}

			// -- Mouse Messages --
		case WM_MOUSEMOVE:
			{
				const auto [x, y] = MAKEPOINTS(lParam);
				IInput::OnMouseMoved(x, y);
				break;
			}
		case WM_LBUTTONDOWN:
			{
				IInput::OnMouseButtonDown(Mouse::ButtonLeft);
				break;
			}
		case WM_LBUTTONUP:
			{
				IInput::OnMouseButtonUp(Mouse::ButtonLeft);
				break;
			}
		case WM_RBUTTONDOWN:
			{
				IInput::OnMouseButtonDown(Mouse::ButtonRight);
				break;
			}
		case WM_RBUTTONUP:
			{
				IInput::OnMouseButtonUp(Mouse::ButtonRight);
				break;
			}
		case WM_MBUTTONDOWN:
			{
				IInput::OnMouseButtonDown(Mouse::ButtonMiddle);
				break;
			}
		case WM_MBUTTONUP:
			{
				IInput::OnMouseButtonUp(Mouse::ButtonMiddle);
				break;
			}
		case WM_XBUTTONDOWN:
			{
				const UINT button = GET_XBUTTON_WPARAM(wParam);
				if (button == XBUTTON1)
				{
					IInput::OnMouseButtonDown(Mouse::Button3);
				}
				else if (button == XBUTTON2)
				{
					IInput::OnMouseButtonDown(Mouse::Button4);
				}
				else
				{
					BE_ERROR("Button {0} is unknown XButton", button);
				}
				break;
			}
		case WM_XBUTTONUP:
			{
				const UINT button = GET_XBUTTON_WPARAM(wParam);
				if (button == XBUTTON1)
				{
					IInput::OnMouseButtonUp(Mouse::Button3);
				}
				else if (button == XBUTTON2)
				{
					IInput::OnMouseButtonUp(Mouse::Button4);
				}
				else
				{
					BE_ERROR("Button {0} is unknown XButton", button);
				}
				break;
			}
		case WM_MOUSEWHEEL:
			{
				IInput::OnMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));
				break;
			}
		}

		return
			DefWindowProc(hWnd, msg, wParam, lParam);
	}

	WPARAM Window::MapLeftRightKeys(const WPARAM vk, const LPARAM lParam)
	{
		WPARAM newVK;
		const UINT scanCode = (lParam & 0x00ff0000) >> 16;
		const int extended = (lParam & 0x1000000) != 0;

		switch (vk)
		{
		case VK_SHIFT:
			newVK = MapVirtualKey(scanCode, MAPVK_VSC_TO_VK_EX);
			break;
		case VK_CONTROL:
			newVK = extended ? VK_RCONTROL : VK_LCONTROL;
			break;
		case VK_MENU:
			newVK = extended ? VK_RMENU : VK_LMENU;
			break;
		case VK_RETURN:
			newVK = extended ? 0xFF : VK_RETURN;
			break;
		default:
			newVK = vk;
			break;
		}

		return newVK;
	}
}
