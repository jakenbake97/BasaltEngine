#pragma once
#include "BEpch.h"
#include "Basalt/Renderer/RenderContext.h"
#include <d3d11.h>

namespace Basalt
{
	class Dx11Context : public RenderContext
	{	
	private:
		HWND windowHandle;
		
		ID3D11Device* device = nullptr;
		IDXGISwapChain* swapChain = nullptr;
		ID3D11DeviceContext* context = nullptr;
		ID3D11RenderTargetView* renderTarget = nullptr;
		
	public:
		Dx11Context(HWND hwnd);
		~Dx11Context() override;
		Dx11Context(const Dx11Context& other) = delete;
		Dx11Context(Dx11Context&& other) noexcept = delete;
		Dx11Context& operator=(const Dx11Context& other) = delete;
		Dx11Context& operator=(Dx11Context&& other) noexcept = delete;

		void SwapBuffers() override;
		void ClearColor(Color color) override;
	};
}
