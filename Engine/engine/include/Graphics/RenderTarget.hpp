#pragma once

#include "../Library/Librarys.hpp"
#include "../Graphics/DepthStencil.hpp"

namespace engine {

	class RenderTarget {
	private:
		static constexpr int BufferSize{ 2 };

	public:
		RenderTarget();
		~RenderTarget();

		bool init();

		void clearScreen();

		void present();
		
		void setRenderTargets();

		void swapCurrentBackBufferIndex();

		void setBackBroundColor();

		void setRenderTargetView(D3D12_RESOURCE_STATES _before, D3D12_RESOURCE_STATES _after);

	private:

		bool createSwapChain();


	private:
		DXGISwapChain3              swapChain;
		D3D12Resource               renderTargets[BufferSize];
		UINT                        frameIndex;
		D3D12_VIEWPORT              viewPort;
		D3D12_RECT                  scissorRect;
		float                       color[4];

		D3D12DescriptorHeap         descriptorHeap;
		UINT                        descriptorSize;
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[BufferSize];

		DepthStencil depthStencil;

		IDXGIFactory3* factory;
		ID3D12Device* device;
		ID3D12GraphicsCommandList* commandList;
	};

}