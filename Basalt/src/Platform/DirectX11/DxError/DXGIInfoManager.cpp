#include "BEpch.h"
#include "DXGIInfoManager.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Platform/DirectX11/Dx11Context.h"

#pragma comment(lib, "dxguid.lib")

namespace Basalt
{
	DXGIInfoManager::DXGIInfoManager()
	{
		// Define the function signature of DXGIGetDebugInterface
		typedef HRESULT (WINAPI* DXGIGetDebugInterface)(REFIID, void**);

		// load the dll that contains the function DXGIGetDebugInterface
		const auto hModDxgiDebug = LoadLibraryEx(L"dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
		if (hModDxgiDebug == nullptr)
		{
			throw BE_WND_LAST_EXCEPT();
		}

		// get address of DXGIGetDebugInterface in dll
		const auto DxgiGetDebugInterface = static_cast<DXGIGetDebugInterface>(
			reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface"))
		);
		if (DxgiGetDebugInterface == nullptr)
		{
			throw BE_WND_LAST_EXCEPT();
		}

		DX_CHECK(DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), &pDxgiInfoQueue));
	}


	void DXGIInfoManager::Set()
	{
		// set the index (next) so that the next call to GetMessages() will only get errors generated after this call
		next = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	}

	std::vector<DXGIMessage> DXGIInfoManager::GetMessages() const
	{
		std::vector<DXGIMessage> messages;
		const auto end = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
		for (auto i = next; i < end; i++)
		{
			SIZE_T messageLength = 0u;
			// get the size of message i in bytes
			DX_CHECK(pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength));
			// allocate memory for message
			auto bytes = std::make_unique<byte[]>(messageLength);
			auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
			// get the message and push its description into the vector
			DX_CHECK(pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, pMessage, &messageLength));
			DXGIMessage message {pMessage->pDescription, pMessage->Severity};
			messages.emplace_back(message);
		}
		return messages;
	}
}
