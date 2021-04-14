#include "Application.h"

namespace Basalt
{

	Application::Application(String name)
		: applicationName(std::move(name))
	{
	}

	Application::~Application() = default;

	void Application::Run()
	{
		while (true);
	}

	String Application::GetAppName() const
	{
		return applicationName;
	}
}
