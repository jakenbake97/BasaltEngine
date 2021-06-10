#include <Basalt.h>

class Sandbox : public Basalt::Application
{
public:
	Sandbox(): Application("SANDBOX")
	{
	}

	~Sandbox() override = default;
};

std::unique_ptr<Basalt::Application> Basalt::CreateApplication()
{
	return std::make_unique<Sandbox>();
}
