#pragma once
#include "WindowsIncludes.h"
#include "../Basalt/Core.h"

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
