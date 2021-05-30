#pragma once

#include "Basalt/Exception.h"
#include "Basalt/Events/Event.h"

namespace Basalt {
	class String;
}

namespace Basalt::Platform
{
	class WindowsInput;

	class BASALT_API Window
	{
	private:

		int width;
		int height;
		HWND handle;

	public:
		class WindowException : public Exception
		{
		private:
			HRESULT hr;
		public:
			WindowException(int line, String file, HRESULT hr);
			String GetException() const override;
			String GetType() const override;
			static String TranslateErrorCode(HRESULT hr);
			HRESULT GetErrorCode() const;
			String GetErrorString() const;
		};
		
		Window(int width, int height, const String& name);
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&& other) noexcept = default;
		Window& operator=(Window && other) noexcept = default;

		static void HandleWindowResize(HWND hWnd, UINT width, UINT height);

	private:
		class WindowClass
		{
		private:
			static WindowClass wndClass;
			HINSTANCE hInst;

		private:
			WindowClass();
			~WindowClass();
		public:
			static const wchar_t* GetName();
			static HINSTANCE GetInstance();

			WindowClass(const WindowClass&) = delete;
			WindowClass& operator=(const WindowClass&) = delete;
		};
		
		static LRESULT WINAPI HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT WINAPI HandleMsgAdapter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) const;
		static WPARAM MapLeftRightKeys(WPARAM vk, LPARAM lParam);
	};
}

#define BE_WND_EXCEPT(hr) Basalt::Platform::Window::WindowException(__LINE__, __FILE__, hr)
#define BE_WND_LAST_EXCEPT() Basalt::Platform::Window::WindowException(__LINE__, __FILE__, GetLastError())
