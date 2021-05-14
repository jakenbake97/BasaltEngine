#pragma once
#include "Basalt/Core.h"
#include "Basalt/Utility/String.h"

namespace Basalt
{
	class WindowCloseEvent;
	class Event;

	class BASALT_API Application
	{
	private:
		String applicationName;
		
	public:
		Application(String name);
		virtual ~Application();

		int Run();
		String GetAppName() const;

		void OnEvent(Event& event);

		bool OnWindowClose(WindowCloseEvent& event);
	};

	extern Application* CreateApplication();
}
