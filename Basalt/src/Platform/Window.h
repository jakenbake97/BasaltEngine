#pragma once

#include "Basalt/Exception.h"

namespace Basalt {
	class String;
}

namespace Basalt::Platform
{
	
	class BASALT_API Window
	{
	private:
		int width;
		int height;
		HWND handle;

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

	private:
		static LRESULT WINAPI HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT WINAPI HandleMsgAdapter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		void HandleWindowResize(HWND hWnd, UINT width, UINT height) const;
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) const;
	};
}

#define BE_WND_EXCEPT(hr) Basalt::Platform::Window::WindowException(__LINE__, __FILE__, hr)
#define BE_WND_LAST_EXCEPT() Basalt::Platform::Window::WindowException(__LINE__, __FILE__, GetLastError())
