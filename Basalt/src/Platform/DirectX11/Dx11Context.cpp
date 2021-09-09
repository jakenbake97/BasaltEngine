#include "BEpch.h"
#include "Dx11Context.h"

#include <sstream>
#include <d3dcompiler.h>

#include "Dx11Macros.h"
#include "Basalt/Renderer/Buffer.h"
#include "Basalt/Renderer/Renderer.h"
#include "DxError/dxerr.h"

namespace wrl = Microsoft::WRL;

namespace Basalt
{
	
	std::unique_ptr<RenderContext> RenderContext::CreateRenderContext(void* handle)
	{
		return std::make_unique<Dx11Context>(static_cast<HWND>(handle));
	}

	Dx11Context::HResultException::HResultException(int line, const String& file, HRESULT hresult, std::vector<String> errors)
		: Exception(line, file), errorCode(hresult)
	{
		for( const auto& message : errors)
		{
			info += message;
			info.PushBack('\n');
		}
		if (!info.Empty())
		{
			info.PopBack();
		}
	}

	String Dx11Context::HResultException::GetException() const
	{
	
		String exceptionString = GetType() + L"[ERROR CODE]: " + GetErrorCode() + L"\n"
			+ L"[ERROR NAME]: " + GetErrorString() + L"\n"
			+ L"[ERROR DESCRIPTION]: " + GetErrorDescription() + L"\n";
		if (!info.Empty())
		{
			exceptionString += L"[ERROR INFO]: " + GetErrorInfo() + "\n";
		}
		return exceptionString + GetOriginString();
	}

	String Dx11Context::HResultException::GetType() const
	{
		return L"DX11 Graphics Exception";
	}

	String Dx11Context::HResultException::GetErrorCode() const
	{
		std::stringstream ss;
		ss << "0x" << std::hex << std::uppercase << errorCode << std::dec << " (" << (unsigned long)errorCode << ")";
		return ss.str();
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

	String Dx11Context::HResultException::GetErrorInfo() const
	{
		return info;
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
		swapDesc.BufferCount = 2;
		swapDesc.OutputWindow = windowHandle;
		swapDesc.Windowed = TRUE;
		
		if constexpr (MAJOR_VERSION < 10)
		{
			swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		}
		else
		{
			swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		}
		swapDesc.Flags = 0;

		uint32 layerFlags = 0;
#ifdef BE_DEBUG
		layerFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		
		DX_INFO_CHECK(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, layerFlags, nullptr, 0, 
			D3D11_SDK_VERSION, &swapDesc, &swapChain, &device, nullptr, &context));

		// gain access to texture subresource in swap chain
		wrl::ComPtr<ID3D11Resource> backBuffer;
		DX_INFO_CHECK(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer));
		DX_INFO_CHECK(device->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTarget));
	}

	void Dx11Context::SwapBuffers()
	{
		DX_DEVICE_REMOVED_CHECK(swapChain->Present(1u, 0u));
	}

	void Dx11Context::ClearColor(Color color)
	{
		const float clearColor[] = { color.r, color.g, color.b, color.a };
		context->ClearRenderTargetView(renderTarget.Get(), clearColor);
	}

	void Dx11Context::DrawTestTriangle(float angle)
	{

		// create vertex array
		const std::vector<Vertex> vertices = 
		{
			{{0.0f, 0.5f}, {255, 25, 255, 255}},
			{{0.5f, -0.5f}, {25, 50, 255, 255}},
			{{-0.5f, -0.5f}, {255, 255, 25, 255}},
			//{{-0.3f, 0.3f}, {0, 255, 0, 255}},
			//{{0.3f, 0.3f}, {0,0,255,255}},
			//{{0.0f, -1.0f}, {255, 0, 0, 255}},
		};
		 
		// index array
		const std::vector<uint32> indices
		{
			0,1,2,
			//0,2,3,
			//0,4,1,
			//2,1,5,
		};

		BufferLayout layout = {
			{"Position", ShaderDataType::Float3},
			{"Color", ShaderDataType::Float4}
		};

		// Create and bind the Vertex Buffer
		const std::unique_ptr<VertexBuffer> vertexBuffer(VertexBuffer::Create(vertices));

		// Create and bind the index Buffer
		const std::unique_ptr<IndexBuffer> indexBuffer(IndexBuffer::Create(indices));

		// create constant buffer for transformation matrix
		struct ConstantBuffer
		{
			Mat4x4 transformation;
		};

		const ConstantBuffer cb =
		{
			{
				(9.0f / 16.0f) * std::cos(angle), std::sin(angle), 0.0f, 0.0f,
				(9.0f / 16.0f) * -std::sin(angle), std::cos(angle), 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
			}
		};

		wrl::ComPtr<ID3D11Buffer> constantBuf;
		D3D11_BUFFER_DESC bufDesc = {};
		bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufDesc.MiscFlags = 0u;
		bufDesc.ByteWidth = sizeof(cb);
		bufDesc.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA subresourceData = {};
		subresourceData.pSysMem = &cb;

		DX_INFO_CHECK(device->CreateBuffer(&bufDesc, &subresourceData, &constantBuf));

		context->VSSetConstantBuffers(0u, 1u, constantBuf.GetAddressOf());

		// create pixel shader
		wrl::ComPtr<ID3D11PixelShader> pixelShader;
		wrl::ComPtr<ID3DBlob> blob;
		DX_INFO_CHECK(D3DReadFileToBlob(L"../Basalt/PixelShader.cso", &blob));
		DX_INFO_CHECK(device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader));

		//bind pixel shader
		context->PSSetShader(pixelShader.Get(), nullptr, 0u);

		// create vertex shader
		wrl::ComPtr<ID3D11VertexShader> vertexShader;
		DX_INFO_CHECK(D3DReadFileToBlob(L"../Basalt/VertexShader.cso", &blob));
		DX_INFO_CHECK(device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertexShader));

		//bind vertex shader
		context->VSSetShader(vertexShader.Get(), nullptr, 0u);

		// input vertex layout (2d positions only & Color)
		wrl::ComPtr<ID3D11InputLayout> inputLayout;

		std::vector<D3D11_INPUT_ELEMENT_DESC> inElementDesc =
		{
			{"POSITION", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u},
			{"COLOR", 0u, DXGI_FORMAT_R8G8B8A8_UNORM, 0u, 8u, D3D11_INPUT_PER_VERTEX_DATA, 0u},
		};

		DX_INFO_CHECK(device->CreateInputLayout(inElementDesc.data(), (uint32)inElementDesc.size(), blob->GetBufferPointer(), blob->GetBufferSize(), inputLayout.GetAddressOf()));

		// bind vertex layout
		context->IASetInputLayout(inputLayout.Get());

		//bind render target
		context->OMSetRenderTargets(1u, renderTarget.GetAddressOf(), nullptr);

		//Set primitive topology to triangle list
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// configure viewport
		D3D11_VIEWPORT viewport = {};
		viewport.Width = 1280;
		viewport.Height = 720;
		viewport.MinDepth = 0;
		viewport.MaxDepth = 1;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		context->RSSetViewports(1u, &viewport);

		//context->Draw((uint32)vertices.size(), 0u);
		context->DrawIndexed((uint32)indices.size(), 0u, 0u);
	}

	void* Dx11Context::GetDevice()
	{
		return device.Get();
	}
	void* Dx11Context::GetDeviceContext()
	{
		return context.Get();
	}
}
