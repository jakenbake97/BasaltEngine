#pragma once
#include "Basalt/Core.h"
#include "Basalt/Utility/String.h"
#include <queue>

#include "Events/Event.h"

namespace Basalt
{
	class WindowCloseEvent;

	class BASALT_API Application
	{
	private:
		String applicationName;
		std::queue<std::shared_ptr<Event>> eventBuffer;
		static Application* instance;
		
	public:
		Application(String name);
		virtual ~Application();

		int Run();
		String GetAppName() const;
		void EventUpdate();

		static void OnEvent(const std::shared_ptr<Event>& event);
		static bool OnWindowClose(WindowCloseEvent& event);
	};

	extern Application* CreateApplication();
}
