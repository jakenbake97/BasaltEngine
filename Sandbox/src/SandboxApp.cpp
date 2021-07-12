#include "Basalt.h"

class WindowLayer : public Basalt::Layer
{
public:
	WindowLayer() : Layer("Window") {}

	void OnUpdate(const float deltaTime) override
	{
	}

	void OnEvent(std::shared_ptr<Basalt::Event>& event) override
	{
	}
};

class InputLayer : public Basalt::Layer
{
public:
	InputLayer() : Layer("Input") {}

	void OnUpdate(float deltaTime) override
	{
	}

	void OnEvent(std::shared_ptr<Basalt::Event>& event) override
	{
	}
};

class Sandbox : public Basalt::Application
{
public:
	Sandbox(): Application("SANDBOX")
	{
		PushLayer(std::make_shared<WindowLayer>());
		PushLayer(std::make_shared<InputLayer>());
	}

	~Sandbox() override = default;
};

std::unique_ptr<Basalt::Application> Basalt::CreateApplication()
{
	return std::make_unique<Sandbox>();
}
