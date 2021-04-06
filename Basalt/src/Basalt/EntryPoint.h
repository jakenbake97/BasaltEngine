#pragma once
#include <cstdio>

#include "Application.h"

#ifdef BAS_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
	printf("Basalt Engine\n");
	
	auto* app = Basalt::CreateApplication();
	app->Run();
	delete app;
}

#endif