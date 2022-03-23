#include "Basalt.h"
#include "imgui/imgui.h"

class ExampleLayer : public Basalt::Layer
{
public:
	ExampleLayer() : Layer("Example"), cam(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		cubeShader = Basalt::Shader::Create("../Basalt/FirstShader-v.cso", "../Basalt/FirstShader-p.cso");
		cubeShader->Bind();

		struct Vertex
		{
			Basalt::Vector3 position;
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
		const std::vector<Basalt::uint32> indices
		{
			0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4,
		};

		// Create and bind the index Buffer
		auto indexBuffer = Basalt::IndexBuffer::Create(indices);

		// input vertex layout (2d positions only & Color)
		const Basalt::BufferLayout layout = {
			{"Position", Basalt::ShaderDataType::Float3},
		};

		// Create and bind the Vertex Buffer
		auto vertexBuffer(Basalt::VertexBuffer::Create<Vertex>(vertices, cubeShader, layout));
		vertexBuffer->Bind();

		vertexArray = std::make_shared<Basalt::VertexArray>(vertexBuffer, indexBuffer);

		vertexConstantBuffer = Basalt::ConstantBuffer<VertexCBuffData>::Create();
		vertexConstantBuffer->Bind(Basalt::ShaderType::Vertex);

		const PixelCBuffData pixelCB{};

		pixelConstantBuffer = Basalt::ConstantBuffer<PixelCBuffData>::Create(pixelCB);
		pixelConstantBuffer->Bind(Basalt::ShaderType::Fragment);

		cam.SetPosition({ 0,0,-5 });
	}

	void OnUpdate(const float deltaTime) override
	{
		lastTime = deltaTime;
		Basalt::Vector3 camPosition = cam.GetPosition();
		float camRotation = cam.GetRotation();

		// This should really be put on an input layer
		if (Basalt::Input::GetKey(Basalt::Key::W))
		{
			camPosition.y += 1.0f * deltaTime;
		}
		if (Basalt::Input::GetKey(Basalt::Key::S))
		{
			camPosition.y -= 1.0f * deltaTime;
		}
		if (Basalt::Input::GetKey(Basalt::Key::A))
		{
			camPosition.x -= 1.0f * deltaTime;
		}
		if (Basalt::Input::GetKey(Basalt::Key::D))
		{
			camPosition.x += 1.0f * deltaTime;
		}
		if (Basalt::Input::GetKey(Basalt::Key::Q))
		{
			camRotation += 10.0f * deltaTime;
		}
		if (Basalt::Input::GetKey(Basalt::Key::E))
		{
			camRotation -= 10.0f * deltaTime;
		}
		cam.SetPosition(camPosition);
		cam.SetRotation(camRotation);

		Basalt::Renderer::BeginScene();

		const Basalt::Mat4x4 cubeScale = glm::scale(Basalt::Mat4x4(1.0f), Basalt::Vector3(0.1f));

		Basalt::Vector4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		Basalt::Vector4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				Basalt::Vector3 cubePos(i * 0.25f, j * 0.25f, 1.0f);
				const Basalt::Mat4x4 model = glm::translate(Basalt::Mat4x4(1.0f), cubePos) *
					cubeScale;

				const Basalt::Mat4x4 transposedMVP = cam.GetViewProjectionMatrix() * model;

				const VertexCBuffData cb =
				{
					{
						glm::transpose(transposedMVP)
					}
				};

				vertexConstantBuffer->UpdateData(cb);

				PixelCBuffData pixelCBuff
				{
					{squareColor}
				};


				pixelConstantBuffer->UpdateData(pixelCBuff);

				Basalt::Renderer::Submit(cubeShader, vertexArray);
			}
		}

		Basalt::Renderer::EndScene();
	}

	void OnEvent(std::shared_ptr<Basalt::Event>& event) override
	{
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::Text("Frame Time: %f | %f fps", lastTime * 1000.0, 1.0/lastTime);
		ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));
		ImGui::End();
	}

	Basalt::OrthographicCamera cam;
	float lastTime;
	struct VertexCBuffData
	{
		Basalt::Mat4x4 transformation;
	};

	struct PixelCBuffData
	{
		Basalt::Vector4 faceColor;
	};

	std::shared_ptr<Basalt::Shader> cubeShader;
	std::shared_ptr<Basalt::VertexArray> vertexArray;

	Basalt::Vector4 squareColor;

	std::shared_ptr<Basalt::ConstantBuffer<VertexCBuffData>> vertexConstantBuffer;
	std::shared_ptr<Basalt::ConstantBuffer<PixelCBuffData>> pixelConstantBuffer;
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
