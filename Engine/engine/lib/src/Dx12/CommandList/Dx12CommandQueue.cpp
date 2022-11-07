#include "Dx12CommandQueue.hpp"
#include "../Device/Device.hpp"
#include "../CommandList/Dx12CommandList.hpp"

namespace engine {

	Dx12CommandQueue::Dx12CommandQueue()
		: commandQueue(nullptr)
		, fence()
		, fenceEvent()
		, fenceValue(0)
		, device(nullptr)
		, commandList(nullptr)
	{
	}

	Dx12CommandQueue::~Dx12CommandQueue()
	{
		waitForPrevousFrame();
		CloseHandle(fenceEvent);
		OutputDebugString("Dx12CommandQueue destructor called. \n");
	}

	bool Dx12CommandQueue::init(device_ptr _device, commandList_ptr _commandList)
	{
		assert(_device != nullptr);
		assert(_commandList != nullptr);

		// device = static_cast<Dx12Device*>(_device.get())->get();
		// commandList = static_cast<Dx12CommandList*>(_commandList.get())->get();

		device = std::dynamic_pointer_cast<Dx12Device>(_device);
		commandList = std::dynamic_pointer_cast<Dx12CommandList>(_commandList);

		HRESULT hr{};

		// コマンドキューの作成
		{
			D3D12_COMMAND_QUEUE_DESC desc{};
			desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
			desc.Priority = 0;
			desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			hr = device->get()->CreateCommandQueue(
				&desc,
				IID_PPV_ARGS(commandQueue.GetAddressOf())
			);

			if (FAILED(hr)) {
				return false;
			}
		}

		{
			hr = device->get()->CreateFence(
				0,
				D3D12_FENCE_FLAG_NONE,
				IID_PPV_ARGS(fence.GetAddressOf())
			);
			if (FAILED(hr)) {
				return false;
			}

			fenceValue = 1;

			fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
			if (!fenceEvent) {
				hr = HRESULT_FROM_WIN32(GetLastError());
				if (FAILED(hr)) {
					return false;
				}
			}

			waitForPrevousFrame();
		}

		return true;
	}

	void Dx12CommandQueue::executeCommand(commandList_ptr _commandList)
	{
		ID3D12CommandList* pCmdList[]{
			static_cast<Dx12CommandList*>(_commandList.get())->get()
		};

		commandQueue->ExecuteCommandLists(_countof(pCmdList), pCmdList);
	}

	void Dx12CommandQueue::waitForPrevousFrame()
	{
		// 実行したコマンドの終了を待つ
		const UINT64 fValue{ fenceValue };
		commandQueue->Signal(fence.Get(), fValue);
		++fenceValue;

		if (fence->GetCompletedValue() < fValue) {
			fence->SetEventOnCompletion(fValue, fenceEvent);
			WaitForSingleObject(fenceEvent, INFINITE);
		}
	}

	std::shared_ptr<core::ICommandQueue> createCommandQueue() {
		return std::shared_ptr<Dx12CommandQueue> {
			new Dx12CommandQueue{}
		};
	}
}