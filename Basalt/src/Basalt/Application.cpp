#include "BEpch.h"
#include "Application.h"

#include "IInput.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvent.h"

namespace Basalt
{
	Application* Application::instance = nullptr;


	Application::Application(String name)
		: applicationName(std::move(name))
	{
		instance = this;

		const String className(L"Basalt Engine");

		BE_WARN("Class Name: {0}, App Name: {1}", className, name);

		const String windowName = className + L" - " + name;
		
		window = IWindow::Create({windowName});
	}

	Application::~Application() = default;

	void Application::Update()
	{
		while (running)
		{
			// Update message loop
			window->OnUpdate();

			for (const auto& layer : layerStack)
				layer->OnUpdate();
			
			EventUpdate();
			
			// Frame Update
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
			BE_TRACE("Event Buffer: {0}", *event);
			
			EventDispatcher dispatcher(*event);
			dispatcher.Dispatch<WindowCloseEvent>([](WindowCloseEvent& closeEvent)->bool {return OnWindowClose(closeEvent); });
			dispatcher.Dispatch<AppQuitEvent>([this](AppQuitEvent& quitEvent)->bool {return this->Quit(quitEvent); });

			for (auto iterator = layerStack.rbegin(); iterator != layerStack.rend(); ++iterator)
			{
				if (event->handled)
					break;
				(*iterator)->OnEvent(*event);
			}
			
			eventBuffer.pop();
		}
	}

	int Application::GetExitCode() const
	{
		return exitCode;
	}

	void Application::PushLayer(const std::shared_ptr<Layer> layer)
	{
		layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(const std::shared_ptr<Layer> overlay)
	{
		layerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(const std::shared_ptr<Event>& event)
	{	
		instance->eventBuffer.push(event);
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		return true;
	}

	bool Application::Quit(AppQuitEvent& event)
	{
		running = false;
		exitCode = event.GetExitCode();
		if (exitCode != 0)
		{
			BE_ERROR("Exited with Code {0}", exitCode);
		}

		system("pause");
		return true;
	}
}
