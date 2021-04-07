#pragma once

#include <string>

#include "Core.h"

namespace Basalt
{
	class BASALT_API Application
	{
	public:
		Application(std::string name);
		virtual ~Application();

		void Run();
		std::string GetAppName() const;
	private:
		std::string applicationName;
	};

	extern Application* CreateApplication();
}
