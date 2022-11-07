#pragma once

#include "../Library/Librarys.hpp"
#include "../../../include/ISwapChain.hpp"
#include "../../../include/Fwd.hpp"

namespace engine {

	class Dx12SwapChain : public core::ISwapChain {
	public:
		Dx12SwapChain();
		~Dx12SwapChain();

		bool init(
			window_ptr _window, factory_ptr _factory, device_ptr _device, commandQueue_ptr _commandQueue
		) override;

		void present() override;

		D3D12_CPU_DESCRIPTOR_HANDLE getCurrenrHandle();

		ID3D12Resource* getCurrentResource();

	private:
		static constexpr int BufferSize{ 2 };
		DXGISwapChain3              swapChain;
		D3D12Resource               renderTargets[BufferSize];
		UINT                        frameIndex;

		D3D12DescriptorHeap         descriptorHeap;
		UINT                        descriptorSize;
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[BufferSize];
	};

}