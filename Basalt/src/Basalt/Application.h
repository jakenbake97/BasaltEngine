#pragma once
#include "Basalt/Core.h"
#include "Basalt/Utility/String.h"
#include <queue>

#include "Events/Event.h"

namespace Basalt
{
	class IWindow;
	class AppQuitEvent;
	class WindowCloseEvent;

	class BASALT_API Application
	{
	private:
		String applicationName;
		std::queue<std::shared_ptr<Event>> eventBuffer;
		static Application* instance;
		bool running = true;
		std::unique_ptr<IWindow> window;
		int exitCode = 0;

		bool Quit(AppQuitEvent& event);
		
	public:
		Application(String name);
		virtual ~Application();

		void Update();
		String GetAppName() const;
		void EventUpdate();
		int GetExitCode() const;

		static void OnEvent(const std::shared_ptr<Event>& event);
		static bool OnWindowClose(WindowCloseEvent& event);
	};

	extern std::unique_ptr<Application> CreateApplication();
}
