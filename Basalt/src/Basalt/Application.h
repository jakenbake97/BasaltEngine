#pragma once
#include "Basalt/Core.h"
#include "Basalt/Utility/String.h"
#include <queue>

#include "LayerStack.h"
#include "Events/Event.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/OrthographicCamera.h"

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
		Application(String name);
		virtual ~Application();
		Application(const Application& other) = delete;
		Application(Application&& other) noexcept = delete;
		Application& operator=(const Application& other) = delete;
		Application& operator=(Application&& other) noexcept = delete;

		static Application& Get() { return *instance; }

		String GetAppName() const;
		void EventUpdate();
		int GetExitCode() const;
		static void OnEvent(const std::shared_ptr<Event>& event);
		void PushLayer(const std::shared_ptr<Layer>& layer);
		void PushOverlay(const std::shared_ptr<Layer>& overlay);

		Window& GetWindow() const { return *window; }
		
	private:
		void Update();
		
		bool OnWindowClose(WindowCloseEvent& event);
		bool Quit(const AppQuitEvent& event);

		friend int ::WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd);

	private:
		String applicationName;
		std::queue<std::shared_ptr<Event>> eventBuffer;
		bool running = true;
		std::unique_ptr<Window> window;

		int exitCode = 0;
		Timer timer;

		LayerStack layerStack;
		std::shared_ptr<ImGuiLayer> imGuiLayer;

		struct VertexCBuffData
		{
			Mat4x4 transformation;
		};

		struct PixelCBuffData
		{
			Vector4 faceColors[6];
		};

		std::shared_ptr<class Shader> firstShader;
		std::shared_ptr<VertexArray> vertexArray;

		std::shared_ptr<ConstantBuffer<VertexCBuffData>> vertexConstantBuffer;
		std::shared_ptr<ConstantBuffer<PixelCBuffData>> pixelConstantBuffer;

		static Application* instance;

		OrthographicCamera cam;
	};

	extern std::unique_ptr<Application> CreateApplication();
}
