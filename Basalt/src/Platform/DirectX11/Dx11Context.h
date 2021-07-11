#pragma once
#include "BEpch.h"
#include "Basalt/Renderer/RenderContext.h"
#include <d3d11.h>
#include "Basalt/Exception.h"
#include "DxError/DXGIInfoManager.h"

namespace Basalt
{
#define DX_CHECK(hresult) DxCheck(hresult, __LINE__, __FILE__)
#define DX_INFO_CHECK(hresult) DxInfoCheck(hresult, __LINE__, __FILE__)
#define DX_DEVICE_REMOVED_CHECK(hresult) DxRemovedCheck(hresult, __LINE__, __FILE__)
	
	class Dx11Context : public RenderContext
	{
	public:
		class HResultException : public Exception
		{
		private:
			HRESULT errorCode;
			String info;
		public:
			HResultException(int line, String file, HRESULT hresult, std::vector<String> errors = {});
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
		
		ID3D11Device* device = nullptr;
		IDXGISwapChain* swapChain = nullptr;
		ID3D11DeviceContext* context = nullptr;
		ID3D11RenderTargetView* renderTarget = nullptr;

#ifdef BE_DEBUG
		DXGIInfoManager infoManager;
#endif
		
		
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
		void DxInfoCheck(HRESULT hresult, const int line, const String& file);
	};

	static constexpr void DxCheck(HRESULT hresult, const int line, const String& file)
	{
		
		if (!FAILED(hresult)) return;
		throw Dx11Context::HResultException(line, file, hresult);
	}
}
