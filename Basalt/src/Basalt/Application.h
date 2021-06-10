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

	class BASALT_API Application
	{
	private:
		String applicationName;
		std::queue<std::shared_ptr<Event>> eventBuffer;
		static Application* instance;
		bool running = true;
		std::unique_ptr<IWindow> window;
		int exitCode = 0;

		LayerStack layerStack;
		
	public:
		Application(String name);
		virtual ~Application();

		void Update();
		String GetAppName() const;
		void EventUpdate();
		int GetExitCode() const;

		void PushLayer(std::shared_ptr<Layer> layer);
		void PushOverlay(std::shared_ptr<Layer> overlay);

		static void OnEvent(const std::shared_ptr<Event>& event);
		static bool OnWindowClose(WindowCloseEvent& event);
	private:
		bool Quit(AppQuitEvent& event);
	};

	extern std::unique_ptr<Application> CreateApplication();
}
