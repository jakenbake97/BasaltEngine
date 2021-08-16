#pragma once

#include "Basalt/Exception.h"
#include "Basalt/IWindow.h"
#include "Basalt/Renderer/RenderContext.h"

namespace Basalt {
	class String;

	class Window : public IWindow
	{
	private:
		WindowProperties properties;
		HWND handle;
		bool vSync;
		bool focused = true;
		std::unique_ptr<RenderContext> graphicsContext;

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
	private:
		class WindowClass
		{
		private:
			static WindowClass wndClass;
			HINSTANCE hInst;

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
		};
	public:
		Window(const WindowProperties& properties);
		~Window() override;
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&& other) noexcept = delete;
		Window& operator=(Window && other) noexcept = delete;
		
		void OnUpdate() override;
		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;

		RenderContext& GetRenderContext() override;
		
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		
	private:
		static void HandleWindowResize(HWND hWnd, UINT width, UINT height);
		
		static LRESULT WINAPI HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT WINAPI HandleMsgAdapter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static WPARAM MapLeftRightKeys(WPARAM vk, LPARAM lParam);
	};
	
	static void constexpr HresultCheck(HRESULT hr, const int line, const Basalt::String& file)
	{
		if (!FAILED(hr)) return;
		throw Window::WindowException(line, file, hr);
	}

#define HR_CHECK(hr) HresultCheck(hr, __LINE__, __FILE__)

#define BE_WND_LAST_EXCEPT() Basalt::Window::WindowException(__LINE__, __FILE__, GetLastError())
}


