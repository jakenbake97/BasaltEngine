#include "Basalt.h"
#include "imgui/imgui.h"

class ExampleLayer : public Basalt::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate(const float deltaTime) override
	{
	}

	void OnEvent(std::shared_ptr<Basalt::Event>& event) override
	{
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}
};

class Sandbox : public Basalt::Application
{
public:
	Sandbox()
	: Application("SANDBOX")
	{
		PushLayer(std::make_shared<ExampleLayer>());
	}

	~Sandbox() override = default;
};

std::unique_ptr<Basalt::Application> Basalt::CreateApplication()
{
	return std::make_unique<Sandbox>();
}
