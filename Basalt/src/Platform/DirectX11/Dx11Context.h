#pragma once
#include "BEpch.h"
#include "Basalt/Renderer/RenderContext.h"
#include <d3d11.h>
#include "Basalt/Exception.h"

namespace Basalt
{
	class Dx11Context : public RenderContext
	{
	public:
		class HResultException : public Exception
		{
		private:
			HRESULT errorCode;
		public:
			HResultException(int line, String file, HRESULT hresult);
			String GetException() const override;
			String GetType() const override;
			HRESULT GetErrorCode() const;
			String GetErrorString() const;
			String GetErrorDescription() const;
		};
		class DeviceRemovedException : public HResultException
		{
			using HResultException::HResultException;
		public:
			String GetType() const override;
		};
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
	private:
		void DxRemovedCheck(HRESULT hresult, const int line, const String& file) const;
	};

	static constexpr void DxCheck(HRESULT hresult, const int line, const String& file)
	{
		if (!FAILED(hresult)) return;
		throw Dx11Context::HResultException(line, file, hresult);
	}
}
