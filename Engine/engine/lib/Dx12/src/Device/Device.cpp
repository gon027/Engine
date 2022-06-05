#include <include/Device/Device.hpp>
#include <include/Device/Adapter.hpp>

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
            adapter[1], D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(device.GetAddressOf())
        );
        if (FAILED(hr)) {
            return false;
        }

        debugValidity(device.Get());

		return true;
	}

    /*

    bool Device::createCommandAllocator(D3D12_COMMAND_LIST_TYPE _type, ID3D12CommandAllocator** _commandAllocator)
    {
        auto hr = device->CreateCommandAllocator(_type, IID_PPV_ARGS(_commandAllocator));
        return SUCCEEDED(hr);
    }

    bool Device::createCommandList(UINT _nodeMask, D3D12_COMMAND_LIST_TYPE _type, ID3D12CommandAllocator* _commandAllocator, ID3D12PipelineState* _pipelineState, ID3D12CommandList** _commandList)
    {
        auto hr = device->CreateCommandList(_nodeMask, _type, _commandAllocator, _pipelineState, IID_PPV_ARGS(_commandList));
        return SUCCEEDED(hr);
    }

    bool Device::createcommandQueue(const D3D12_COMMAND_QUEUE_DESC* _desc, ID3D12CommandQueue** _commandQueue)
    {
        auto hr = device->CreateCommandQueue(_desc, IID_PPV_ARGS(_commandQueue));
        return SUCCEEDED(hr);
    }

    bool Device::createCommittedResource(const D3D12_HEAP_PROPERTIES* _prop, D3D12_HEAP_FLAGS _flags, const D3D12_RESOURCE_DESC* _desc, D3D12_RESOURCE_STATES _states, const D3D12_CLEAR_VALUE* _value, ID3D12Resource** _resouce)
    {
        auto hr = device->CreateCommittedResource(
            _prop, _flags, _desc, _states, _value, IID_PPV_ARGS(_resouce)
        );
        return SUCCEEDED(hr);
    }

    void Device::createConstantBufferView(const D3D12_CONSTANT_BUFFER_VIEW_DESC* _desc, D3D12_CPU_DESCRIPTOR_HANDLE _handle)
    {
        device->CreateConstantBufferView(_desc, _handle);
    }

    void Device::createDepthStencilView(ID3D12Resource* _resource, const D3D12_DEPTH_STENCIL_VIEW_DESC* _desc, D3D12_CPU_DESCRIPTOR_HANDLE _handle)
    {
        device->CreateDepthStencilView(_resource, _desc, _handle);
    }

    bool Device::createDescriptorHeap(const D3D12_DESCRIPTOR_HEAP_DESC* _desc, ID3D12DescriptorHeap** _descriptorHeap)
    {
        auto hr = device->CreateDescriptorHeap(_desc, IID_PPV_ARGS(_descriptorHeap));
        return SUCCEEDED(hr);
    }

    bool Device::createFence(UINT64 _initialValue, D3D12_FENCE_FLAGS _flags, ID3D12Fence** _fence)
    {
        auto hr = device->CreateFence(_initialValue, _flags, IID_PPV_ARGS(_fence));
        return SUCCEEDED(hr);
    }

    bool Device::createGraphicsPipelineState(const D3D12_GRAPHICS_PIPELINE_STATE_DESC* _desc, ID3D12PipelineState** _pipelineState)
    {
        auto hr = device->CreateGraphicsPipelineState(_desc, IID_PPV_ARGS(_pipelineState));
        return SUCCEEDED(hr);
    }

    bool Device::createComputePipelineState(D3D12_COMPUTE_PIPELINE_STATE_DESC* _desc, ID3D12PipelineState** _pipelineState)
    {
        auto hr = device->CreateComputePipelineState(_desc, IID_PPV_ARGS(_pipelineState));
        return SUCCEEDED(hr);
    }

    void Device::createRenderTargetView(ID3D12Resource* _resource, const D3D12_RENDER_TARGET_VIEW_DESC* _desc, D3D12_CPU_DESCRIPTOR_HANDLE _handle)
    {
        device->CreateRenderTargetView(_resource, _desc, _handle);
    }

    bool Device::createRootSignature(UINT _nodeMask, const void* _bufferPointer, size_t _bufferSize, ID3D12RootSignature** _rootSignature)
    {
        auto hr = device->CreateRootSignature(_nodeMask, _bufferPointer, _bufferSize, IID_PPV_ARGS(_rootSignature));
        return SUCCEEDED(hr);
    }

    void Device::createSampler(const D3D12_SAMPLER_DESC* _desc, D3D12_CPU_DESCRIPTOR_HANDLE _handle)
    {
        device->CreateSampler(_desc, _handle);
    }

    void Device::createShaderResourceView(ID3D12Resource* _resource, const D3D12_SHADER_RESOURCE_VIEW_DESC* _desc, D3D12_CPU_DESCRIPTOR_HANDLE _handle)
    {
        device->CreateShaderResourceView(_resource, _desc, _handle);
    }

    void Device::createUnorderedAccessView(ID3D12Resource* _resource, ID3D12Resource* _counterResouce, const D3D12_UNORDERED_ACCESS_VIEW_DESC* _desc, D3D12_CPU_DESCRIPTOR_HANDLE _handle)
    {
        device->CreateUnorderedAccessView(_resource, _counterResouce, _desc, _handle);
    }

    UINT Device::getDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE _type)
    {
        return device->GetDescriptorHandleIncrementSize(_type);
    }
    */
}