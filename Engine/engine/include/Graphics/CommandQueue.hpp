#pragma once

#include "../Library/Librarys.hpp"

namespace engine {

	class CommandQueue {
	public:
		CommandQueue();
		~CommandQueue();

		bool init();

		void executeCommand();

		void waitForPrevousFrame();

		inline ID3D12CommandQueue* const get() const {
			return commandQueue.Get();
		}

		inline ID3D12CommandQueue* const operator->() const {
			return commandQueue.Get();
		}

	private:
		D3D12CommandQueue commandQueue;
		D3D12Fence fence;
		HANDLE fenceEvent;
		UINT64 fenceValue;

	private:
		ID3D12Device* device;
		ID3D12CommandList* commandList;
	};

}