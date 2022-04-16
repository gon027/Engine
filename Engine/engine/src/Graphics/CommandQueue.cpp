#include "../../include/Graphics/CommandQueue.hpp"
#include "../../include/EngineCore/EngineCore.hpp"
#include "../../include/Graphics/Device.hpp"
#include "../../include/Graphics/CommandList.hpp"

namespace engine {

	CommandQueue::CommandQueue()
		: commandQueue(nullptr)
		, fence()
		, fenceEvent()
		, fenceValue(0)
		, device(nullptr)
		, commandList(nullptr)
	{
	}

	CommandQueue::~CommandQueue()
	{
		waitForPrevousFrame();
		CloseHandle(fenceEvent);
	}

	bool CommandQueue::init()
	{
		{
			if (!device) device = EngineDevice()->get();
			if (!commandList) commandList = EngineCommand()->get();
		}

		HRESULT hr{};

		// コマンドキューの作成
		{
			D3D12_COMMAND_QUEUE_DESC desc{};
			desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
			desc.Priority = 0;
			desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			hr = device->CreateCommandQueue(
				&desc,
				IID_PPV_ARGS(commandQueue.GetAddressOf())
			);
			if (FAILED(hr)) {
				return false;
			}
		}

		{
			hr = device->CreateFence(
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

	void CommandQueue::executeCommand()
	{
		ID3D12CommandList* pCmdList[]{
			// commandList
			EngineCommand()->get()
		};
		commandQueue->ExecuteCommandLists(_countof(pCmdList), pCmdList);
	}

	void CommandQueue::waitForPrevousFrame()
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
}