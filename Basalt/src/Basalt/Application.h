#pragma once
#include "Basalt/Core.h"
#include "Basalt/Utility/String.h"
#include <queue>

#include "LayerStack.h"
#include "Events/Event.h"
#include "ImGui/ImGuiLayer.h"

namespace Basalt
{
	class AppQuitEvent;
	template<typename T>
	class ConstantBuffer;
	class Timer;
	class VertexArray;
	class Window;
	class WindowCloseEvent;
	
	class Application
	{
	public:
		/// <summary>
		/// Creates the base Basalt Engine application
		/// </summary>
		/// <param name="name"></param>
		Application(String name);
		virtual ~Application();
		Application(const Application& other) = delete;
		Application(Application&& other) noexcept = delete;
		Application& operator=(const Application& other) = delete;
		Application& operator=(Application&& other) noexcept = delete;

		/// <summary>
		/// Returns a reference to the instance of the application
		/// </summary>
		/// <returns>the static instance of the engine application</returns>
		static Application& Get() { return *instance; }

		/// <summary>
		/// Returns the name of the application/project
		/// </summary>
		/// <returns>The string name of the project</returns>
		String GetAppName() const;
		/// <summary>
		/// Loops through all events currently in queue and dispatches them to each layer until they are handled
		/// </summary>
		void EventUpdate();
		/// <summary>
		/// Gets the exit code for the program on quit
		/// </summary>
		/// <returns>The exit code indicating success or failure</returns>
		int GetExitCode() const;
		/// <summary>
		/// Pushes events onto the event queue as they occur
		/// </summary>
		/// <param name="event">The event to add to the queue</param>
		static void OnEvent(const std::shared_ptr<Event>& event);
		/// <summary>
		/// Pushes a layer onto the layer stack
		/// </summary>
		/// <param name="layer">The layer to push onto the stack</param>
		void PushLayer(const std::shared_ptr<Layer>& layer);
		/// <summary>
		/// Pushes an overlay onto the layer stack. Overlays are placed after normal layers
		/// </summary>
		/// <param name="overlay">The overlay layer to push onto the stack</param>
		void PushOverlay(const std::shared_ptr<Layer>& overlay);

		/// <summary>
		/// Returns a reference to the window that the application runs in
		/// </summary>
		/// <returns>A reference to the application window</returns>
		Window& GetWindow() const { return *window; }
		
	private:
		void Update();
		
		bool OnWindowClose(WindowCloseEvent& event);
		bool Quit(const AppQuitEvent& event);

		friend int ::WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd);

	public:
		static Timer Time;
	private:
		String applicationName;
		std::queue<std::shared_ptr<Event>> eventBuffer;
		bool running = true;
		std::unique_ptr<Window> window;

		int exitCode = 0;

		LayerStack layerStack;
		std::shared_ptr<ImGuiLayer> imGuiLayer;

		static Application* instance;
	};

	extern std::unique_ptr<Application> CreateApplication();
}
