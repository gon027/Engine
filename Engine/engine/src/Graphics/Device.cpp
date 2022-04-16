#include "../../include/Graphics/Device.hpp"
#include "../../include/Graphics/Adapter.hpp"

#include <string>
#include <vector>

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
                D3D12_MESSAGE_ID_CLEARDEPTHSTENCILVIEW_MISMATCHINGCLEARVALUE
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

            infoQueue->PushStorageFilter(&filter);

            // エラーが発生したときブレークする
            // D3D12_ERRORが発生したとき、デバッガで停止させることができる
            infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);

        #endif
		}

    }

	Device::Device()
		: device(nullptr)
	{
	}

	Device::~Device()
	{
        device.Reset();
	}

	bool Device::init(IDXGIFactory3* _factory)
	{
        HRESULT hr{};

        Adapter adapter{};
        adapter.init(_factory);

		hr = D3D12CreateDevice(
            adapter(1), D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(device.GetAddressOf())
        );
        if (FAILED(hr)) {
            return false;
        }

        debugValidity(device.Get());

		return true;
	}

}