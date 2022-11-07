#include "Device.hpp"
#include "Adapter.hpp"
#include "Factory.hpp"

#include <string>
#include <vector>

#include "../Buffer/Dx12Resource.hpp"

namespace engine {

	namespace {

		void debugValidity(ID3D12Device* _device) {
        #if _DEBUG
            // デバッグメッセージの格納、取得、フィルタリングができる
            Microsoft::WRL::ComPtr<ID3D12InfoQueue> infoQueue;
            auto hr = _device->QueryInterface(IID_PPV_ARGS(&infoQueue));
            // FAILEDRETURN(hr, "Failed QueryInterface ... \n");

            D3D12_MESSAGE_ID denyIds[]{
                // D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE,
                D3D12_MESSAGE_ID_CLEARDEPTHSTENCILVIEW_MISMATCHINGCLEARVALUE,

                // D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE,
                // D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE,
                // D3D12_MESSAGE_ID_EXECUTECOMMANDLISTS_WRONGSWAPCHAINBUFFERREFERENCE,
                D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE,
            };

            D3D12_MESSAGE_SEVERITY severities[]{
                D3D12_MESSAGE_SEVERITY_CORRUPTION,  // 破損エラーを表示
                D3D12_MESSAGE_SEVERITY_ERROR,       // エラーを表示
                D3D12_MESSAGE_SEVERITY_WARNING,     // 警告を表示
                D3D12_MESSAGE_SEVERITY_INFO,        // 情報メッセージを示す
                // D3D12_MESSAGE_SEVERITY_MESSAGE      // 破損、エラー、警告以外のメッセージを表示させる
            };

            D3D12_INFO_QUEUE_FILTER filter{};
            filter.DenyList.NumIDs = _countof(denyIds);
            filter.DenyList.pIDList = denyIds;
            filter.DenyList.NumCategories = _countof(severities);
            filter.DenyList.pSeverityList = severities;
            infoQueue->AddStorageFilterEntries(&filter);

            infoQueue->PushStorageFilter(&filter);

            // エラーが発生したときブレークする
            // D3D12_ERRORが発生したとき、デバッガで停止させることができる
            infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);

        #endif
		}

    }

	Dx12Device::Dx12Device()
		: device(nullptr)
        , adapter()
        , adapterName{ L"" }
	{
	}

	Dx12Device::~Dx12Device()
	{
        device.Reset();
        OutputDebugString("Dx12Device destructor called. \n");
	}

    bool Dx12Device::init(factory_ptr _factory)
    {
        assert(_factory != nullptr);
        
        auto dxFactory = std::dynamic_pointer_cast<Dx12Factory>(_factory);

        // Adapter adapter{};
        if (!adapter.init(dxFactory->get())) {
            return false;
        }

        HRESULT hr = D3D12CreateDevice(
            adapter[0], D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(device.GetAddressOf())
        );
        if (FAILED(hr)) {
            return false;
        }

        adapterName = adapter.getAdapterName();
        // OutputDebugStringW(adapterName.c_str());

        debugValidity(device.Get());

        return true;
    }

    resource_ptr Dx12Device::createResource(
        const HeapType& _type, const ResourceDesc& _desc,
        ResouceStates _status, const ClearValue* _clearValue
    )
    {
        /*
        auto result = std::shared_ptr<core::Resource>(new Dx12Resource{});
        result->init(this, _type, _desc, _status, _clearValue);
        */
        return nullptr;
    }

    std::shared_ptr<core::IDevice> createDevice() {
        return std::shared_ptr<Dx12Device> {
            new Dx12Device{}
        };
    }

}