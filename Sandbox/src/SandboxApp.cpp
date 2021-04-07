#include <Basalt.h>

class Sandbox : public Basalt::Application
{
public:
	Sandbox(): Application("SANDBOX")
	{
	}

	~Sandbox() override = default;
};

Basalt::Application* Basalt::CreateApplication()
{
	return new Sandbox();
}
