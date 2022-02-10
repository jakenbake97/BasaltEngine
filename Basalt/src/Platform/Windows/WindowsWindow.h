#pragma once

#include "Basalt/Exception.h"
#include "Basalt/Window.h"
#include "Basalt/Renderer/RenderContext.h"

namespace Basalt {
	class String;

	class WindowsWindow : public Window
	{
	public:
		class WindowException : public Exception
		{
		public:
			WindowException(int line, String file, HRESULT hr);
			String GetException() const override;
			String GetType() const override;
			static String TranslateErrorCode(HRESULT hr);
			HRESULT GetErrorCode() const;
			String GetErrorString() const;
		private:
			HRESULT hr;
		};
	private:
		class WindowClass
		{
		public:
			static const wchar_t* GetName();
			static HINSTANCE GetInstance();

			WindowClass(const WindowClass& other) = delete;
			WindowClass(WindowClass&& other) noexcept = delete;
			WindowClass& operator=(const WindowClass& other) = delete;
			WindowClass& operator=(WindowClass&& other) noexcept = delete;
		private:
			WindowClass();
			~WindowClass();

		private:
			static WindowClass wndClass;
			HINSTANCE hInst;
		};
	public:
		WindowsWindow(const WindowProperties& properties);
		~WindowsWindow() override;
		WindowsWindow(const WindowsWindow&) = delete;
		WindowsWindow& operator=(const WindowsWindow&) = delete;
		WindowsWindow(WindowsWindow&& other) noexcept = delete;
		WindowsWindow& operator=(WindowsWindow && other) noexcept = delete;
		
		void OnUpdate() override;
		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;

		void* GetWindowHandle() const override;
		
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		
	private:
		static void HandleWindowResize(HWND hWnd, UINT width, UINT height);
		
		static LRESULT WINAPI HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT WINAPI HandleMsgAdapter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static WPARAM MapLeftRightKeys(WPARAM vk, LPARAM lParam);

		WindowProperties properties;
		HWND handle;
		bool vSync;
		bool focused = true;
	};
	
	static void constexpr HresultCheck(HRESULT hr, const int line, const Basalt::String& file)
	{
		if (!FAILED(hr)) return;
		throw WindowsWindow::WindowException(line, file, hr);
	}

#define HR_CHECK(hr) HresultCheck(hr, __LINE__, __FILE__)

#define BE_WND_LAST_EXCEPT() Basalt::WindowsWindow::WindowException(__LINE__, __FILE__, GetLastError())
}


