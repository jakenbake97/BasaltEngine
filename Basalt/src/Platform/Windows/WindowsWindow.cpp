#include "BEpch.h"
#include "WindowsWindow.h"

#include <utility>

#include "WindowsInput.h"
#include "Basalt/Application.h"
#include "Basalt/Input.h"
#include "Basalt/Utility/String.h"
#include "Basalt/Log.h"
#include "Basalt/Events/ApplicationEvent.h"
#include "Basalt/Events/WindowEvent.h"
#include "Basalt/Events/KeyboardEvent.h"
#include "atlstr.h"
#include <backends/imgui_impl_win32.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Basalt
{
	Scope<Window> Window::Create(const WindowProperties& properties)
	{
		return std::make_unique<WindowsWindow>(properties);
	}

	WindowsWindow::WindowException::WindowException(const int line, String file, const HRESULT hr)
		: Exception(line, std::move(file)), hr(hr)
	{
	}

	String WindowsWindow::WindowException::GetException() const
	{
		return GetType()
			+ "\n[Error Code] " + GetErrorCode()
			+ "\n[Description] " + GetErrorString()
			+ GetOriginString();
	}

	String WindowsWindow::WindowException::GetType() const
	{
		return "Basalt Window Exception";
	}

	String WindowsWindow::WindowException::TranslateErrorCode(const HRESULT hr)
	{
		wchar_t* msgBuf = nullptr;

		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			reinterpret_cast<LPWSTR>(&msgBuf), 0, nullptr) == 0)
		{
			return "Unidentified error code";
		}
		String errorString = msgBuf;
		LocalFree(msgBuf);
		return errorString;
	}

	HRESULT WindowsWindow::WindowException::GetErrorCode() const
	{
		return hr;
	}

	String WindowsWindow::WindowException::GetErrorString() const
	{
		return TranslateErrorCode(hr);
	}
	
	WindowsWindow::WindowClass WindowsWindow::WindowClass::wndClass;

	WindowsWindow::WindowClass::WindowClass()
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
		wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = GetName();
		wc.hIconSm = nullptr;

		RegisterClassEx(&wc);
	}

	WindowsWindow::WindowClass::~WindowClass()
	{
		UnregisterClass(GetName(), GetInstance());
	}

	const wchar_t* WindowsWindow::WindowClass::GetName()
	{
		return L"Basalt Engine";
	}

	HINSTANCE WindowsWindow::WindowClass::GetInstance()
	{
		return wndClass.hInst;
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
		: properties(properties), vSync(false)
	{
		RECT windowRect;
		windowRect.left = 0;
		windowRect.right = properties.width;
		windowRect.top = 0;
		windowRect.bottom = properties.height;

		constexpr auto styles = WS_OVERLAPPEDWINDOW;

		if (!AdjustWindowRect(&windowRect, styles, false))
		{
			throw BE_WND_LAST_EXCEPT();
		}


		handle = CreateWindow(WindowClass::GetName(), CString(properties.title.CStr()),
		                      styles, CW_USEDEFAULT, CW_USEDEFAULT,
		                      windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
		                      nullptr, nullptr,
		                      WindowClass::GetInstance(), this
		);

		if (!handle)
		{
			throw BE_WND_LAST_EXCEPT();
		}

		ShowWindow(handle, SW_SHOWDEFAULT);

		BE_TRACE("{0} x {1} Window Successfully Created!", properties.width, properties.height);
	}

	WindowsWindow::~WindowsWindow()
	{
		if (handle != nullptr && !DestroyWindow(handle))
		{
			BE_ERROR("Destroy Window failed [LINE] {0} in [FILE] {1}", __LINE__, __FILE__);
		}
	}

	LRESULT WINAPI WindowsWindow::HandleMsgSetup(HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam)
	{
		// use the create parameter passed in from CreateWindow() to store window class pointer
		if (msg == WM_NCCREATE)
		{
			// extract ptr to window class from creation data
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			const auto pWindow = static_cast<WindowsWindow*>(pCreate->lpCreateParams);
			// set WinAPI-managed user data to store ptr to window class
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
			// set message proc to normal (non-setup) handler now that setup is finished
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WindowsWindow::HandleMsgAdapter));
			// forward message to window class message handler
			return pWindow->HandleMsg(hWnd, msg, wParam, lParam);
		}
		// if a message comes before the WM_NCCREATE message, handle with the default handler
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	LRESULT WINAPI WindowsWindow::HandleMsgAdapter(HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam)
	{
		// retrieve ptr to window class
		auto* const pWindow = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		// forward message to the window class message handler
		return pWindow->HandleMsg(hWnd, msg, wParam, lParam);
	}

	void WindowsWindow::OnUpdate()
	{
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0,0,PM_REMOVE))
		{
			// Check for quit message and create an event if the application should quit
			if (msg.message == WM_QUIT)
			{
				const auto event = std::make_shared<AppQuitEvent>((int)msg.wParam);
				Application::OnEvent(event);
				handle = nullptr;
				return;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	unsigned WindowsWindow::GetWidth() const
	{
		return properties.width;
	}

	unsigned WindowsWindow::GetHeight() const
	{
		return properties.height;
	}

	void* WindowsWindow::GetWindowHandle() const
	{
		return handle;
	}

	void WindowsWindow::SetVSync(const bool enabled)
	{
		vSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return vSync;
	}

	void WindowsWindow::HandleWindowResize(HWND hWnd, UINT width, UINT height)
	{
		RECT clientRect, windowRect;
		POINT pointDiff;
		GetClientRect(hWnd, &clientRect);
		GetWindowRect(hWnd, &windowRect);
		pointDiff.x = (windowRect.right - windowRect.left) - clientRect.right;
		pointDiff.y = (windowRect.bottom - windowRect.top) - clientRect.bottom;
		MoveWindow(hWnd, windowRect.left, windowRect.top, width + pointDiff.x, height + pointDiff.y, TRUE);
	}

	LRESULT WindowsWindow::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		{
			return true;
		}

		switch (msg)
		{
			// -- Window Messages --
		case WM_CLOSE:
			{
				const auto event = std::make_shared<WindowCloseEvent>(0);
				Application::OnEvent(event);

				break;
			}
		case WM_DESTROY:
			{
				PostQuitMessage(0);
				break;
			}
		case WM_SIZE:
			{
				HandleWindowResize(hWnd, LOWORD(lParam), HIWORD(lParam));
				const auto event = std::make_shared<WindowResizeEvent>(LOWORD(lParam), HIWORD(lParam));
				Application::OnEvent(event);

				break;
			}
		case WM_MOVE:
			{
				const auto [x, y] = MAKEPOINTS(lParam);
				const auto event = std::make_shared<WindowMovedEvent>(Vector2Int(x,y));
				Application::OnEvent(event);

				break;
			}
		case WM_SETFOCUS:
			{
				focused = true;
				const auto event = std::make_shared<WindowFocusEvent>();
				Application::OnEvent(event);

				break;
			}
		case WM_KILLFOCUS:
			{
				ClearInputState();
				focused = false;
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
					const KeyCode basaltCode = Key::WindowsToBasaltKeyCode.at(static_cast<unsigned char>(virtualCode));
					OnKeyDown(basaltCode);
				}
				break;
			}
		case WM_SYSKEYUP:
		case WM_KEYUP:
			{
				const WPARAM virtualCode = MapLeftRightKeys(wParam, lParam);
				const KeyCode basaltCode = Key::WindowsToBasaltKeyCode.at(static_cast<unsigned char>(virtualCode));
				OnKeyUp(basaltCode);

				break;
			}

			// -- Mouse Messages --
		case WM_MOUSEMOVE:
			{
				const auto [x, y] = MAKEPOINTS(lParam);

				// The mouse is over the client
				if (x >= 0 && x < (short)properties.width && y >= 0 && y < (short)properties.height)
				{
					OnMouseMoved({x,y});
					if (!Input::IsMouseInWindow())
					{
						SetCapture(hWnd);
						OnMouseEnter();
					}
				}
					// not in client, but maintain capture if a button is held
				else
				{
					if (wParam & (MK_LBUTTON | MK_RBUTTON | MK_MBUTTON | MK_XBUTTON1 | MK_XBUTTON2))
					{
						OnMouseMoved({x, y});
					}
						// no button pressed, release capture
					else
					{
						ReleaseCapture();
						OnMouseLeave();
					}
				}
				break;
			}
		case WM_LBUTTONDOWN:
			{
				OnMouseButtonDown(Mouse::ButtonLeft);
				if (Input::IsMouseInWindow() && !focused)
				{
					SetActiveWindow(hWnd);
				}
				break;
			}
		case WM_LBUTTONUP:
			{
				OnMouseButtonUp(Mouse::ButtonLeft);
				break;
			}
		case WM_RBUTTONDOWN:
			{
				OnMouseButtonDown(Mouse::ButtonRight);
				if (Input::IsMouseInWindow() && !focused)
				{
					SetActiveWindow(hWnd);
				}
				break;
			}
		case WM_RBUTTONUP:
			{
				OnMouseButtonUp(Mouse::ButtonRight);
				break;
			}
		case WM_MBUTTONDOWN:
			{
				OnMouseButtonDown(Mouse::ButtonMiddle);
				if (Input::IsMouseInWindow() && !focused)
				{
					SetActiveWindow(hWnd);
				}
				break;
			}
		case WM_MBUTTONUP:
			{
				OnMouseButtonUp(Mouse::ButtonMiddle);
				break;
			}
		case WM_XBUTTONDOWN:
			{
				const UINT button = GET_XBUTTON_WPARAM(wParam);
				if (button == XBUTTON1)
				{
					OnMouseButtonDown(Mouse::Button3);
				}
				else if (button == XBUTTON2)
				{
					OnMouseButtonDown(Mouse::Button4);
				}
				else
				{
					BE_ERROR("Button {0} is unknown XButton", button);
				}

				if (Input::IsMouseInWindow() && !focused)
				{
					SetActiveWindow(hWnd);
				}
				
				break;
			}
		case WM_XBUTTONUP:
			{
				const UINT button = GET_XBUTTON_WPARAM(wParam);
				if (button == XBUTTON1)
				{
					OnMouseButtonUp(Mouse::Button3);
				}
				else if (button == XBUTTON2)
				{
					OnMouseButtonUp(Mouse::Button4);
				}
				else
				{
					BE_ERROR("Button {0} is unknown XButton", button);
				}
				break;
			}
		case WM_MOUSEWHEEL:
			{
				OnMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));
				break;
			}
		}
		return
			DefWindowProc(hWnd, msg, wParam, lParam);
	}

	WPARAM WindowsWindow::MapLeftRightKeys(const WPARAM vk, const LPARAM lParam)
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
