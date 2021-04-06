#pragma once

#include "Core.h"

namespace Basalt
{
	class BASALT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	extern Application* CreateApplication();
}
