#pragma once
#include "Dx11Context.h"
#include "Basalt/Renderer/Renderer.h"

namespace Basalt
{
	class Dx11Checks
	{
#ifdef BE_DEBUG
		inline static DXGIInfoManager infoManager{};
#endif
	public:
		static constexpr void DxCheck(HRESULT hresult, const int line, const String& file)
		{
			if (!FAILED(hresult)) return;
			throw Dx11Context::HResultException(line, file, hresult);
		}

		static void DxInfoCheck(HRESULT hresult, const int line, const String& file)
		{
#ifdef BE_DEBUG
			auto messages = infoManager.GetMessages();
			infoManager.Set();

			std::vector<String> errorDescriptions{};

			for (auto& message : messages)
			{
				if (message.severity == DXGI_INFO_QUEUE_MESSAGE_SEVERITY_WARNING)
				{
					BE_WARN("DXGI: {0}", message.description);
				}

				if (message.severity == DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR)
				{
					if (!FAILED(hresult))
						BE_ERROR("DXGI: {0}", message.description);
					errorDescriptions.emplace_back(message.description);
				}
			}
			if (!FAILED(hresult)) return;
			throw Dx11Context::HResultException(line, file, hresult, errorDescriptions);
#endif
			DxCheck(hresult, line, file);
		}

		static void DxRemovedCheck(HRESULT hresult, const int line, const String& file)
		{
			{
				std::vector<String> errorDescriptions{};
#ifdef BE_DEBUG
				auto messages = infoManager.GetMessages();
				infoManager.Set();


				for (auto& message : messages)
				{
					if (message.severity == DXGI_INFO_QUEUE_MESSAGE_SEVERITY_WARNING)
					{
						BE_WARN("DXGI: {0}", message.description);
					}

					if (message.severity == DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR)
					{
						if (!FAILED(hresult))
							BE_ERROR("DXGI: {0}", message.description);
						errorDescriptions.emplace_back(message.description);
					}
				}
#endif
				if (!FAILED(hresult)) return;
				if (hresult == DXGI_ERROR_DEVICE_REMOVED)
				{
					throw Dx11Context::DeviceRemovedException(line, file, static_cast<ID3D11Device*>(Renderer::GetRenderContext().GetDevice())->GetDeviceRemovedReason(), errorDescriptions);
				}
				DxCheck(hresult, line, file);
			}
		}
	};

#define DX_CHECK(hResult) Dx11Checks::DxCheck(hResult, __LINE__, __FILE__)
#define DX_INFO_CHECK(hResult) Dx11Checks::DxInfoCheck(hResult, __LINE__, __FILE__)
#define DX_DEVICE_REMOVED_CHECK(hResult) Dx11Checks::DxRemovedCheck(hResult, __LINE__, __FILE__)
}
