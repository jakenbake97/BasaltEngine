#include <Basalt.h>

class Sandbox : public Basalt::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{
		
	}
};

Basalt::Application* Basalt::CreateApplication()
{
	return new Sandbox();
}