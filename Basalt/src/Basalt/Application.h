#pragma once

#include "Core.h"
#include "Utility/String.h"

namespace Basalt
{
	class BASALT_API Application
	{
	private:
		String applicationName;	
	public:
		Application(String name);
		virtual ~Application();

		int Run();
		String GetAppName() const;
	};

	extern Application* CreateApplication();
}
