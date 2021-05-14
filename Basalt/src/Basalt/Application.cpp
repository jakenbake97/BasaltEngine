#include "BEpch.h"
#include "Application.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvent.h"

namespace Basalt
{
	Application::Application(String name)
		: applicationName(std::move(name))
	{
		
	}

	Application::~Application() = default;

	int Application::Run()
	{
		
		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (gResult == -1)
		{
			return EXIT_FAILURE;
		}

		return msg.wParam;
	}

	String Application::GetAppName() const
	{
		return applicationName;
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& event)->bool {return OnWindowClose(event); });
		BE_TRACE(event);
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		system("pause");

		if (event.GetExitCode() != 0)
			return false;
		
		return true;
	}
}
