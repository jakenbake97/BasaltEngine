#include "Application.h"

namespace Basalt
{

	Application::Application(std::string name)
		: applicationName(std::move(name))
	{
	}

	Application::~Application() = default;

	void Application::Run()
	{
		while (true);
	}

	std::string Application::GetAppName() const
	{
		return applicationName;
	}
}
