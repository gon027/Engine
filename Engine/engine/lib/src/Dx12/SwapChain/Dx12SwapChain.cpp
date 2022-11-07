#include "Dx12SwapChain.hpp"
#include "../../Windows/Window.hpp"
#include "../Device/Device.hpp"
#include "../Device/Factory.hpp"
#include "../CommandList/Dx12CommandQueue.hpp"

namespace engine {

	Dx12SwapChain::Dx12SwapChain()
		: swapChain(nullptr)
		, renderTargets()
		, descriptorHeap(nullptr)
		, descriptorSize(0)
		, rtvHandles()
		, frameIndex(0)
	{
	}

	Dx12SwapChain::~Dx12SwapChain()
	{
		OutputDebugString("Dx12SwapChain destructor called. \n");
	}

	bool Dx12SwapChain::init(
		window_ptr _window, factory_ptr _factory, device_ptr _device, commandQueue_ptr _commandQueue
	)
	{
		assert(_window != nullptr);
		assert(_factory != nullptr);
		assert(_device != nullptr);
		assert(_commandQueue != nullptr);

		auto* factory = static_cast<Dx12Factory*>(_factory.get());
		auto* device = static_cast<Dx12Device*>(_device.get());
		auto* commandQueue = static_cast<Dx12CommandQueue*>(_commandQueue.get());
		auto* window = static_cast<Window*>(_window.get());

		HRESULT hr{};

		// DescriptorHeapの作成
		{
			D3D12_DESCRIPTOR_HEAP_DESC desc{};
			desc.NumDescriptors = BufferSize;
			desc.NodeMask = 0;
			desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

			hr = device->get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(descriptorHeap.GetAddressOf()));
			if (FAILED(hr)) {
				return false;
			}

			descriptorSize = device->get()->GetDescriptorHandleIncrementSize(desc.Type);
		}

		{
			// スワップチェインの作成
			DXGI_SWAP_CHAIN_DESC1 desc{};
			// desc.Width = EngineWindow()->getWidth();
			// desc.Height = EngineWindow()->getHeight();
			desc.Width = 640;
			desc.Height = 480;
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			desc.SampleDesc.Count = 1;
			desc.SampleDesc = { .Count = 1, .Quality = 0 };
			desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			desc.BufferCount = BufferSize;
			desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
			desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

			ComPtr<IDXGISwapChain1> t_swapChain1{ nullptr };
			
			HRESULT hr = factory->get()->CreateSwapChainForHwnd(
				commandQueue->get(),
				window->getHWnd(),
				&desc,
				nullptr,
				nullptr,
				t_swapChain1.GetAddressOf()
			);

			if (FAILED(hr)) {
				return false;
			}

			t_swapChain1.As(&swapChain);

			for (UINT i{ 0 }; i < BufferSize; ++i) {
				hr = swapChain->GetBuffer(i, IID_PPV_ARGS(renderTargets[i].GetAddressOf()));

				if (FAILED(hr)) {
					return false;
				}

				rtvHandles[i] = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
				rtvHandles[i].ptr += static_cast<size_t>(i * descriptorSize);
				device->get()->CreateRenderTargetView(renderTargets[i].Get(), nullptr, rtvHandles[i]);
			}

			frameIndex = swapChain->GetCurrentBackBufferIndex();

		}

		return true;
	}

	void Dx12SwapChain::present()
	{
		swapChain->Present(1, 0);
		frameIndex = swapChain->GetCurrentBackBufferIndex();
	}

	ID3D12Resource* Dx12SwapChain::getCurrentResource()
	{
		return renderTargets[frameIndex].Get();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE Dx12SwapChain::getCurrenrHandle()
	{
		return rtvHandles[frameIndex];
	}

	std::shared_ptr<core::ISwapChain> createSwapChain()
	{
		return std::shared_ptr<Dx12SwapChain> {
			new Dx12SwapChain{}
		};
	}

}