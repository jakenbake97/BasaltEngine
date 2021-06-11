#include <Basalt.h>

class ExampleLayer : public Basalt::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		
	}

	void OnEvent(std::shared_ptr<Basalt::Event>& event) override
	{
		BE_TRACE("ExampleLayer::Event {0}", *event);
	}
};

class Sandbox : public Basalt::Application
{
public:
	Sandbox(): Application("SANDBOX")
	{
		PushLayer(std::make_shared<ExampleLayer>());
	}

	~Sandbox() override = default;
};

std::unique_ptr<Basalt::Application> Basalt::CreateApplication()
{
	return std::make_unique<Sandbox>();
}
