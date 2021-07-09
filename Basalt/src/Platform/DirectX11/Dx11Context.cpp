#include "BEpch.h"
#include "Dx11Context.h"

#include <utility>

#include "DxError/dxerr.h"

namespace Basalt
{
#define DX_CHECK(hresult) DxCheck(hresult, __LINE__, __FILE__)
#define DX_DEVICE_REMOVED_CHECK(hresult) DxRemovedCheck(hresult, __LINE__, __FILE__)
	
	std::unique_ptr<RenderContext> RenderContext::CreateRenderContext(void* handle)
	{
		return std::make_unique<Dx11Context>(static_cast<HWND>(handle));
	}

	Dx11Context::HResultException::HResultException(int line, String file, HRESULT hresult)
		: Exception(line, std::move(file)), errorCode(hresult)
	{
	}

	String Dx11Context::HResultException::GetException() const
	{
		return GetType() + L" [ERROR CODE]: " + GetErrorCode()
			+ L" [ERROR NAME]: " + GetErrorString()
			+ L" [ERROR DESCRIPTION]: " + GetErrorDescription() + GetOriginString();
	}

	String Dx11Context::HResultException::GetType() const
	{
		return L"DX11 Graphics Exception";
	}

	HRESULT Dx11Context::HResultException::GetErrorCode() const
	{
		return errorCode;
	}

	String Dx11Context::HResultException::GetErrorString() const
	{
		return DXGetErrorString(errorCode);
	}

	String Dx11Context::HResultException::GetErrorDescription() const
	{
		WCHAR buf[512];
		DXGetErrorDescription(errorCode, buf, 512);
		return buf;
	}

	String Dx11Context::DeviceRemovedException::GetType() const
	{
		return L"DX11 Graphics Exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
	}

	Dx11Context::Dx11Context(HWND hwnd)
		: windowHandle(hwnd)
	{
		DXGI_SWAP_CHAIN_DESC swapDesc = {};
		swapDesc.BufferDesc.Width = 0;
		swapDesc.BufferDesc.Height = 0;
		swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapDesc.BufferDesc.RefreshRate.Denominator = 0;
		swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapDesc.SampleDesc.Count = 1;
		swapDesc.SampleDesc.Quality = 0;
		swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapDesc.BufferCount = 1;
		swapDesc.OutputWindow = (HWND)12345;//windowHandle;
		swapDesc.Windowed = TRUE;
		swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapDesc.Flags = 0;

		UINT layerFlags = 0;
#ifdef BE_DEBUG
		layerFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		
		DX_CHECK(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, layerFlags, nullptr, 0, 
			D3D11_SDK_VERSION, &swapDesc, &swapChain, &device, nullptr, &context));

		// gain access to texture subresource in swap chain
		ID3D11Resource* backBuffer = nullptr;
		DX_CHECK(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
		DX_CHECK(device->CreateRenderTargetView(backBuffer, nullptr, &renderTarget));
		backBuffer->Release();
	}

	Dx11Context::~Dx11Context()
	{
		if (renderTarget != nullptr)
		{
			renderTarget->Release();
		}
		if (context != nullptr)
		{
			context->Release();
		}
		if (swapChain != nullptr)
		{
			swapChain->Release();
		}
		if (device != nullptr)
		{
			device->Release();
		}
	}

	void Dx11Context::SwapBuffers()
	{
		DX_DEVICE_REMOVED_CHECK(swapChain->Present(1u, 0u));
	}

	void Dx11Context::ClearColor(Color color)
	{
		const float clearColor[] = { color.r, color.g, color.b, color.a };
		context->ClearRenderTargetView(renderTarget, clearColor);
	}

	void Dx11Context::DxRemovedCheck(HRESULT hresult, const int line, const String& file) const
	{
		if (!FAILED(hresult)) return;
		if (hresult == DXGI_ERROR_DEVICE_REMOVED)
		{
			throw DeviceRemovedException(line, file, device->GetDeviceRemovedReason());
		}
		DxCheck(hresult, line, file);
	}
}
