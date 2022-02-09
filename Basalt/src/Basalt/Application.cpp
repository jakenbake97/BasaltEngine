#include "BEpch.h"
#include "Application.h"

#include "imgui.h"
#include "Input.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvent.h"
#include "Renderer/Buffer.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

namespace Basalt
{
	Application* Application::instance = nullptr;


	Application::Application(String name)
		: applicationName(std::move(name)), cam(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		instance = this;

		const String className(L"Basalt Engine");
		BE_TRACE("Class Name: {0}, App Name: {1}", className, applicationName);
		const String windowName = className + L" - " + applicationName;
		
		window = Window::Create({windowName});
		Renderer::Initialize(window);

		imGuiLayer = std::make_shared<ImGuiLayer>();
		PushOverlay(imGuiLayer);

		firstShader = Shader::Create("../Basalt/FirstShader-v.cso", "../Basalt/FirstShader-p.cso");
		firstShader->Bind();

		struct Vertex
		{
			Vector3 position;
		};

		// create vertex array
		const std::vector<Vertex> vertices =
		{
			{{-1.0f, -1.0f, -1.0f}},
			{{1.0f, -1.0f, -1.0f}},
			{{-1.0f, 1.0f, -1.0f}},
			{{1.0f,1.0f,-1.0f}},
			{{-1.0f, -1.0f, 1.0f}},
			{{1.0f, -1.0f, 1.0f}},
			{{-1.0f, 1.0f, 1.0f}},
			{{1.0f, 1.0f, 1.0f}}
		};

		// index array
		const std::vector<uint32> indices
		{
			0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4,
		};

		// Create and bind the index Buffer
		indexBuffer = IndexBuffer::Create(indices);
		indexBuffer->Bind();

		// input vertex layout (2d positions only & Color)
		const BufferLayout layout = {
			{"Position", ShaderDataType::Float3},
		};

		// Create and bind the Vertex Buffer
		const auto vertexBuffer(VertexBuffer::Create<Vertex>(vertices, firstShader, layout));
		vertexBuffer->Bind();

		vertexConstantBuffer = ConstantBuffer<VertexCBuffData>::Create();
		vertexConstantBuffer->Bind(ShaderType::Vertex);

		const PixelCBuffData pixelCB =
		{
			{
				{0.8f, 0.2f, 0.3f, 1.0f},
				{0.3f, 0.8f, 0.2f, 1.0f},
				{0.2f, 0.3f, 0.8f, 1.0f},
				{0.8f, 0.8f, 0.2f, 1.0f},
				{0.8f, 0.2f, 0.8f, 1.0f},
				{0.2f, 0.8f, 0.8f, 1.0f}
			}
		};
		pixelConstantBuffer = ConstantBuffer<PixelCBuffData>::Create(pixelCB);
		pixelConstantBuffer->Bind(ShaderType::Fragment);

		cam.SetPosition({ 0,0,-5 });
	}

	Application::~Application()
	{
		layerStack.PopOverlay(imGuiLayer);
	}

	void Application::Update()
	{
		while (running)
		{
			timer.Mark();

			Vector3 camPosition = cam.GetPosition();

			// This should really be put on an input layer
			if (Input::GetKey(Key::W))
			{
				camPosition.y += 1.0f * timer.GetDeltaTime();
			}
			if (Input::GetKey(Key::S))
			{
				camPosition.y -= 1.0f * timer.GetDeltaTime();
			}
			if (Input::GetKey(Key::A))
			{
				camPosition.x -= 1.0f * timer.GetDeltaTime();
			}
			if (Input::GetKey(Key::D))
			{
				camPosition.x += 1.0f * timer.GetDeltaTime();
			}
			
			// Frame Update
			RenderCommand::Clear({ 1.0f, 0.25f, 1.0f, 1.0f });

			cam.SetPosition(camPosition);

			Vector3 position(0, 0, 1);

			Mat4x4 model =
				glm::translate(Mat4x4(1.0f), position) *
				glm::rotate(Mat4x4(1.0f), timer.GetTime(), Vector3(0, 0, 1)) *
				glm::rotate(Mat4x4(1.0f), timer.GetTime() / 2.0f, Vector3(0.5f, 0.5f, 0)) *
				glm::scale(Mat4x4(1.0f), Vector3(0.5f, 0.5f, 0.5f));

			Mat4x4 transposedMVP = cam.GetViewProjectionMatrix() * model;

			VertexCBuffData cb =
			{
				{
					glm::transpose(transposedMVP)
				}
			};

			vertexConstantBuffer->UpdateData(cb);
			RenderCommand::DrawIndexed(indexBuffer->GetCount());

			position = Vector3(1,1,1);
			model =
				glm::translate(Mat4x4(1.0f), position) *
				glm::rotate(Mat4x4(1.0f), timer.GetTime() * 4.0f, Vector3(0, 0, 1)) *
				glm::rotate(Mat4x4(1.0f), -timer.GetTime() * 8.0f, Vector3(0.5f, 0.5f, 0));

			transposedMVP = cam.GetViewProjectionMatrix() * model;
			cb.transformation = glm::transpose(transposedMVP);
			vertexConstantBuffer->UpdateData(cb);

			RenderCommand::DrawIndexed(indexBuffer->GetCount());

			// Update message loop
			window->OnUpdate();
			EventUpdate();

			for (const auto& layer : layerStack)
				layer->OnUpdate(timer.GetDeltaTime());

			// Draw ImGui
			imGuiLayer->Begin();

			ImGui::Begin("Camera");
			ImGui::Text("Camera Position: %f, %f, %f", camPosition.x, camPosition.y, camPosition.z);
			ImGui::End();

			for (const auto& layer : layerStack)
				layer->OnImGuiRender();

			imGuiLayer->End();

			// End Frame
			Renderer::GetRenderContext().SwapBuffers();
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
