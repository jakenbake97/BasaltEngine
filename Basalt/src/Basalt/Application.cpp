#include "Application.h"

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
		else
		{
			return msg.wParam;
		}
	}

	String Application::GetAppName() const
	{
		return applicationName;
	}
}
