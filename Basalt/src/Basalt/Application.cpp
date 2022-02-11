#include "BEpch.h"
#include "Application.h"

#include "imgui.h"
#include "Input.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvent.h"
#include "Renderer/Renderer.h"


namespace Basalt
{
	Application* Application::instance = nullptr;

	Timer Application::Time = Timer();


	Application::Application(String name)
		: applicationName(std::move(name))
	{
		instance = this;

		const String className(L"Basalt Engine");
		BE_TRACE("Class Name: {0}, App Name: {1}", className, applicationName);
		const String windowName = className + L" - " + applicationName;
		
		window = Window::Create({windowName});
		Renderer::Initialize(*window);

		imGuiLayer = std::make_shared<ImGuiLayer>();
		PushOverlay(imGuiLayer);
	}

	Application::~Application()
	{
		layerStack.PopOverlay(imGuiLayer);
	}

	void Application::Update()
	{
		while (running)
		{
			Time.Mark();

			// Frame Update
			RenderCommand::Clear();

			// Update message loop
			window->OnUpdate();
			EventUpdate();

			for (const auto& layer : layerStack)
				layer->OnUpdate(Time.GetDeltaTime());

			// Draw ImGui
			imGuiLayer->Begin();

			for (const auto& layer : layerStack)
				layer->OnImGuiRender();

			imGuiLayer->End();

			// End Frame
			RenderCommand::SwapBuffers();
		}		
	}

	String Application::GetAppName() const
	{
		return applicationName;
	}

	void Application::EventUpdate()
	{
		while(!eventBuffer.empty())
		{
			auto event = eventBuffer.front();
			
			EventDispatcher dispatcher(event);
			dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& closeEvent)->bool {return this->OnWindowClose(closeEvent); });
			dispatcher.Dispatch<AppQuitEvent>([this](AppQuitEvent& quitEvent)->bool {return this->Quit(quitEvent); });

			for (auto iterator = layerStack.rbegin(); iterator != layerStack.rend(); ++iterator)
			{
				if (event->IsHandled())
					break;
				(*iterator)->OnEvent(event);
			}
			
			eventBuffer.pop();
		}
	}

	int Application::GetExitCode() const
	{
		return exitCode;
	}

	void Application::PushLayer(const std::shared_ptr<Layer>& layer)
	{
		layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(const std::shared_ptr<Layer>& overlay)
	{
		layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(const std::shared_ptr<Event>& event)
	{	
		instance->eventBuffer.push(event);
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		running = false;
		return true;
	}

	bool Application::Quit(const AppQuitEvent& event)
	{
		running = false;
		exitCode = event.GetExitCode();
		if (exitCode != 0)
		{
			BE_ERROR("Exited with Code {0}", exitCode);
		}
		else
		{
			BE_TRACE("Exited with Code {0}", exitCode);
		}

		return true;
	}
}
