#pragma once
#include "BEpch.h"
#include "Basalt/Renderer/RenderContext.h"
#include <d3d11.h>
#include "Basalt/Exception.h"
#include "DxError/DXGIInfoManager.h"
#include <wrl.h>

namespace Basalt
{
	class Dx11Context : public RenderContext
	{
	public:
		class HResultException : public Exception
		{
		private:
			HRESULT errorCode;
			String info;
		public:
			HResultException(int line, const String& file, HRESULT hresult, std::vector<String> errors = {});
			String GetException() const override;
			String GetType() const override;
			String GetErrorCode() const;
			String GetErrorString() const;
			String GetErrorDescription() const;
			String GetErrorInfo() const;
		};
		class DeviceRemovedException : public HResultException
		{
		private:
			String reason;
			using HResultException::HResultException;
		public:
			String GetType() const override;
		};
	private:
		HWND windowHandle;
		
		Microsoft::WRL::ComPtr<ID3D11Device> device;
		Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTarget;
		
		
	public:
		Dx11Context(HWND hwnd);
		~Dx11Context() override = default;
		Dx11Context(const Dx11Context& other) = delete;
		Dx11Context(Dx11Context&& other) noexcept = delete;
		Dx11Context& operator=(const Dx11Context& other) = delete;
		Dx11Context& operator=(Dx11Context&& other) noexcept = delete;

		void SwapBuffers() override;
		void ClearColor(Color color) override;
		void DrawTestTriangle(float angle) override;
		void* GetDevice() override;
		void* GetDeviceContext() override;
	};

	
}
