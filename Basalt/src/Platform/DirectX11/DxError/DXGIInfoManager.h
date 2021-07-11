#pragma once
#include <vector>
#include <dxgidebug.h>

namespace Basalt
{
	class String;

	struct DXGIMessage
	{
		String description;
		DXGI_INFO_QUEUE_MESSAGE_SEVERITY severity;
	};
	
	class DXGIInfoManager
	{
	private:
		unsigned long long next = 0u;

		IDXGIInfoQueue* pDxgiInfoQueue = nullptr;
	public:
		DXGIInfoManager();
		~DXGIInfoManager();
		DXGIInfoManager(const DXGIInfoManager& other) = delete;
		DXGIInfoManager(DXGIInfoManager&& other) noexcept = delete;
		DXGIInfoManager& operator=(const DXGIInfoManager& other) = delete;
		DXGIInfoManager& operator=(DXGIInfoManager&& other) noexcept = delete;
		
		void Set();
		std::vector<DXGIMessage> GetMessages() const;
	};
	
}
