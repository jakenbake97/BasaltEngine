#include "BEpch.h"
#include "ImGuiLayer.h"

#include "Basalt/Application.h"
#include "Basalt/Window.h"
#include "Basalt/Renderer/Renderer.h"

#include <imgui.h>
#ifdef BE_PLATFORM_WINDOWS
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx11.h"
#endif

namespace Basalt
{
	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer")
	{
	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		const Application& app = Application::Get();
		RenderContext& context = Renderer::GetRenderContext();

#ifdef BE_PLATFORM_WINDOWS
		// Setup Platform/Renderer backends
		ImGui_ImplWin32_Init(app.GetWindow().GetWindowHandle());
		ImGui_ImplDX11_Init(static_cast<ID3D11Device*>(context.GetDevice()), static_cast<ID3D11DeviceContext*>(context.GetDeviceContext()));
#endif
	}

	void ImGuiLayer::OnDetach()
	{
#ifdef BE_PLATFORM_WINDOWS
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
#endif
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void ImGuiLayer::Begin()
	{
		// TODO: Update to use appropriate implementation based on platform (or potentially have a different ImGuiLayer per platform)
		// Start the Dear ImGui frame
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}
}
