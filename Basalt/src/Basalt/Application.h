#pragma once
#include "Basalt/Core.h"
#include "Basalt/Utility/String.h"
#include <queue>

#include "LayerStack.h"
#include "Events/Event.h"

namespace Basalt
{
	class IWindow;
	class AppQuitEvent;
	class WindowCloseEvent;
	class Timer;
	
	class Application
	{
	private:
		String applicationName;
		std::queue<std::shared_ptr<Event>> eventBuffer;
		static Application* instance;
		bool running = true;
		std::unique_ptr<IWindow> window;
		int exitCode = 0;
		Timer timer;

		LayerStack layerStack;
		
	public:
		Application(String name);
		virtual ~Application();
		Application(const Application& other) = delete;
		Application(Application&& other) noexcept = delete;
		Application& operator=(const Application& other) = delete;
		Application& operator=(Application&& other) noexcept = delete;

		void Update();
		String GetAppName() const;
		void EventUpdate();
		int GetExitCode() const;

		void PushLayer(const std::shared_ptr<Layer>& layer);
		void PushOverlay(const std::shared_ptr<Layer>& overlay);

		static void OnEvent(const std::shared_ptr<Event>& event);
		static bool OnWindowClose(WindowCloseEvent& event);
	private:
		bool Quit(AppQuitEvent& event);
	};

	extern std::unique_ptr<Application> CreateApplication();
}
