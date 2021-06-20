#include <Basalt.h>

class WindowLayer : public Basalt::Layer
{
public:
	WindowLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		
	}

	void OnEvent(std::shared_ptr<Basalt::Event>& event) override
	{
		if (event->GetCategories() == static_cast<int>(Basalt::EventCategory::Window))
		{
			BE_TRACE("ExampleLayer::Event {0}", *event);
			event->handled = true;
		}
	}
};

class InputLayer : public Basalt::Layer
{
public:
	InputLayer() : Layer("Input") {}

	void OnUpdate() override
	{
		Mat4x4 tempMat({ 1.1f, 2.2f, 3.3f, 4.4f });
		BE_TRACE(tempMat);
	}

	void OnEvent(std::shared_ptr<Basalt::Event>& event) override
	{
		if (event->GetCategories() == static_cast<int>(Basalt::EventCategory::Keyboard) || 
			event->GetCategories() == static_cast<int>(Basalt::EventCategory::Mouse))
		{
			BE_INFO("InputLayer::Event {0}", *event);
			event->handled = true;
		}
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
