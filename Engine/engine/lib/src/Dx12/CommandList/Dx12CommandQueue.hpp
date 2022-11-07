#pragma once

#include "../Library/Librarys.hpp"
#include "../include/ICommandQueue.hpp"

namespace engine {

	class Dx12CommandQueue : public core::ICommandQueue {
	public:
		Dx12CommandQueue();
		~Dx12CommandQueue();

		bool init(device_ptr _device, commandList_ptr _commandList) override;

		void executeCommand(commandList_ptr _commandList) override;

		void waitForPrevousFrame()override;

		inline ID3D12CommandQueue* const get() const {
			return commandQueue.Get();
		}

	private:
		D3D12CommandQueue commandQueue;
		D3D12Fence fence;
		HANDLE fenceEvent;
		UINT64 fenceValue;

	private:
		// ID3D12Device* device;
		// ID3D12CommandList* commandList;
		std::shared_ptr<class Dx12Device> device;
		std::shared_ptr<class Dx12CommandList> commandList;
	};

}