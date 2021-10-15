#include "BEpch.h"
#include "Dx11Context.h"

#include <sstream>
#include <d3dcompiler.h>

#include "Dx11Macros.h"
#include "Basalt/IWindow.h"
#include "Basalt/Renderer/Buffer.h"
#include "Basalt/Renderer/Renderer.h"
#include "Basalt/Renderer/Shader.h"
#include "DxError/dxerr.h"

namespace wrl = Microsoft::WRL;

namespace Basalt
{
	
	std::unique_ptr<RenderContext> RenderContext::CreateRenderContext(std::unique_ptr<IWindow>& window)
	{
		return std::make_unique<Dx11Context>(window);
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
	
		String exceptionString = GetType() + "[ERROR CODE]: " + GetErrorCode() + "\n"
			+ "[ERROR NAME]: " + GetErrorString() + "\n"
			+ "[ERROR DESCRIPTION]: " + GetErrorDescription() + "\n";
		if (!info.Empty())
		{
			exceptionString += "[ERROR INFO]: " + GetErrorInfo() + "\n";
		}
		return exceptionString + GetOriginString();
	}

	String Dx11Context::HResultException::GetType() const
	{
		return "DX11 Graphics Exception";
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
		return "DX11 Graphics Exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
	}

	Dx11Context::Dx11Context(std::unique_ptr<IWindow>& window)
	{
		windowHandle = static_cast<HWND>(window->GetWindowHandle());

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

		// Create depth stencil state
		D3D11_DEPTH_STENCIL_DESC depthDesc = {};
		depthDesc.DepthEnable = TRUE;
		depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthDesc.DepthFunc = D3D11_COMPARISON_LESS;
		wrl::ComPtr<ID3D11DepthStencilState> depthStencilState;
		DX_INFO_CHECK(device->CreateDepthStencilState(&depthDesc, &depthStencilState));

		// bind depth state
		context->OMSetDepthStencilState(depthStencilState.Get(), 1u);

		// Create depth stencil texture
		wrl::ComPtr<ID3D11Texture2D> depthStencil;
		D3D11_TEXTURE2D_DESC depthTexDesc = {};
		depthTexDesc.Width = window->GetWidth();
		depthTexDesc.Height = window->GetHeight();
		depthTexDesc.MipLevels = 1u;
		depthTexDesc.ArraySize = 1u;
		depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthTexDesc.SampleDesc.Count = 1u;
		depthTexDesc.SampleDesc.Quality = 0u;
		depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		DX_INFO_CHECK(device->CreateTexture2D(&depthTexDesc, nullptr, &depthStencil));

		// create view of depth stencil texture
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
		depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0u;
		DX_INFO_CHECK(device->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, &depthStencilView));

		// bind depth stencil view to pipeline
		context->OMSetRenderTargets(1u, renderTarget.GetAddressOf(), depthStencilView.Get());
	}

	void Dx11Context::SwapBuffers()
	{
		DX_DEVICE_REMOVED_CHECK(swapChain->Present(1u, 0u));
	}

	void Dx11Context::ClearColor(Color color)
	{
		const float clearColor[] = { color.r, color.g, color.b, color.a };
		context->ClearRenderTargetView(renderTarget.Get(), clearColor);
		context->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
	}

	void Dx11Context::DrawTestTriangle(float angle, uint32 width, uint32 height, Vector3 position)
	{
		auto firstShader = Shader::Create("../Basalt/FirstShader-v.cso", "../Basalt/FirstShader-p.cso");
		firstShader->Bind();

		// create constant buffer for transformation matrix
		struct ConstantBuffer
		{
			Mat4x4 transformation;
		};

		const Mat4x4 projection = glm::perspectiveLH(glm::radians(45.0f), (float)width / (float)height , 0.1f, 100.0f);

		const Mat4x4 view = glm::lookAtLH(
		Vector3(0,0,-4),
		Vector3(0,0,0),
		Vector3(0,1,0));

		const Mat4x4 model =
			glm::translate(Mat4x4(1.0f), position) *
			glm::rotate(Mat4x4(1.0f), angle, Vector3(0,0,1)) *
			glm::rotate(Mat4x4(1.0f), angle, Vector3(1,0,0));

		const ConstantBuffer cb =
		{
			{
				glm::transpose(projection * view * model)
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
		//bind constant buffer to the vertex Shader
		context->VSSetConstantBuffers(0u, 1u, constantBuf.GetAddressOf());

		struct PixelConstantBuffer
		{
			Vector4 faceColors[6];
		};

		const PixelConstantBuffer pixelCB =
		{
			{
				{1.0f, 0.0f, 1.0f, 1.0f},
				{1.0f, 0.0f, 0.0f, 0.0f},
				{0.0f, 1.0f, 0.0f, 1.0f},
				{0.0f, 0.0f, 1.0f, 1.0f},
				{1.0f, 1.0f, 0.0f, 1.0f},
				{0.0f, 1.0f, 1.0f, 1.0f}
			}
		};

		wrl::ComPtr<ID3D11Buffer> pixelConstBuf;
		bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufDesc.Usage = D3D11_USAGE_DEFAULT;
		bufDesc.CPUAccessFlags = 0u;
		bufDesc.MiscFlags = 0u;
		bufDesc.ByteWidth = sizeof(pixelCB);
		bufDesc.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA pixelSubResource = {};
		pixelSubResource.pSysMem = &pixelCB;

		DX_INFO_CHECK(device->CreateBuffer(&bufDesc, &pixelSubResource, &pixelConstBuf));
		//bind constant buffer to the vertex Shader
		context->PSSetConstantBuffers(0u, 1u, pixelConstBuf.GetAddressOf());

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
		const std::unique_ptr<IndexBuffer> indexBuffer(IndexBuffer::Create(indices));

		// input vertex layout (2d positions only & Color)
		const BufferLayout layout = {
			{"Position", ShaderDataType::Float3},
		};

		// Create and bind the Vertex Buffer
		const std::unique_ptr<VertexBuffer> vertexBuffer(VertexBuffer::Create<Vertex>(vertices, firstShader, layout));

		vertexBuffer->Bind();

		//Set primitive topology to triangle list
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// bind depth stencil view to pipeline
		context->OMSetRenderTargets(1u, renderTarget.GetAddressOf(), depthStencilView.Get());

		// configure viewport
		D3D11_VIEWPORT viewport = {};
		viewport.Width = (float)width;
		viewport.Height = (float)height;
		viewport.MinDepth = 0;
		viewport.MaxDepth = 1;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		context->RSSetViewports(1u, &viewport);

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
