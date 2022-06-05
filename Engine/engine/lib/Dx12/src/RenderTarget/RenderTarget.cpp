#include <include/RenderTarget/RenderTarget.hpp>
#include <include/EngineCore/EngineCore.hpp>
#include "../../include/Window/Window.hpp"
#include <include/Device/Device.hpp>
#include <include/Device/Factory.hpp>
#include <include/CommandList/CommandList.hpp>
#include <include/CommandList/CommandQueue.hpp>
#include "../../../../include/Color/Color.hpp"

namespace engine {

	RenderTarget::RenderTarget()
		: swapChain(nullptr)
		, renderTargets()
		, descriptorHeap(nullptr)
		, descriptorSize(0)
		, rtvHandles()
		, frameIndex(0)
		, viewPort({})
		, color(ColorF::Black)
		, scissorRect({})
		, depthStencil()
		, factory(nullptr)
		, device(nullptr)
		, commandList(nullptr)
	{
	}

	RenderTarget::~RenderTarget()
	{
	}

	bool RenderTarget::init()
	{
		{
			if (!factory) factory = EngineFactory()->get();
			if (!device) device = EngineDevice()->get();
			if (!commandList) commandList = EngineCommand()->get();
		}

		viewPort.TopLeftX = 0.0f;
		viewPort.TopLeftY = 0.0f;
		viewPort.Width    = 640.0f;
		viewPort.Height   = 480.0f;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;

		scissorRect.top    = 0;
		scissorRect.left   = 0;
		scissorRect.right  = 640;
		scissorRect.bottom = 480;

		// color[0] = 1.0f;
		// color[1] = 1.0f;
		// color[2] = 1.0f;
		// color[3] = 1.0f;

		HRESULT hr{};

		// DescriptorHeapの作成
		{
			D3D12_DESCRIPTOR_HEAP_DESC desc{};
			desc.NumDescriptors = BufferSize;
			desc.NodeMask       = 0;
			desc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			desc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

			hr = device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(descriptorHeap.GetAddressOf()));
			if (FAILED(hr)) {
				return false;
			}

			descriptorSize = device->GetDescriptorHandleIncrementSize(desc.Type);

			auto s = "RenderTarget DescriptorSize = " + std::to_string(descriptorSize) + "\n";
			OutputDebugString(s.c_str());
		}

		if(!createSwapChain()) {
			return false;
		}

		if (!depthStencil.init()) {
			return false;
		}

		return true;
	}

	bool RenderTarget::createSwapChain()
	{
		// スワップチェインの作成
		DXGI_SWAP_CHAIN_DESC1 desc{};

		desc.Width = EngineWindow()->getWidth();
		desc.Height = EngineWindow()->getHeight();
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc = { .Count = 1, .Quality = 0 };
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = BufferSize;
		desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		ComPtr<IDXGISwapChain1> t_swapChain1{ nullptr };
		HRESULT hr = factory->CreateSwapChainForHwnd(
			EngineCommandQueue()->get(),
			EngineWindow()->getHWnd(),
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
			device->CreateRenderTargetView(renderTargets[i].Get(), nullptr, rtvHandles[i]);
		}

		swapCurrentBackBufferIndex();

		return true;
	}

	void RenderTarget::clearScreen()
	{
		// ビューポート設定
		commandList->RSSetViewports(1, &viewPort);

		// シザー矩形の設定
		commandList->RSSetScissorRects(1, &scissorRect);

		// レンダーターゲットのクリア
		auto handle = rtvHandles[frameIndex];
		// auto s = "RenderTarget Handle = " + std::to_string(handle.ptr) + "\n";
		// OutputDebugString(s.c_str());
		commandList->ClearRenderTargetView(handle, color.rgba, 0, nullptr);
	}

	void RenderTarget::present()
	{
		swapChain->Present(1, 0);
	}

	void RenderTarget::setRenderTargets()
	{
		const auto pDepthStencilDescriptor = depthStencil.getDepth()->GetCPUDescriptorHandleForHeapStart();
		commandList->OMSetRenderTargets(
			1, &rtvHandles[frameIndex], 0, &pDepthStencilDescriptor
		);

		// 深度ステンシルのクリア
		depthStencil.clearDepthStencil();
	}

	void RenderTarget::swapCurrentBackBufferIndex()
	{
		frameIndex = swapChain->GetCurrentBackBufferIndex();
	}

	void RenderTarget::setBackBroundColor(const ColorF& _color)
	{
		color = _color;
	}

	void RenderTarget::setRenderTargetView(D3D12_RESOURCE_STATES _before, D3D12_RESOURCE_STATES _after)
	{
		D3D12_RESOURCE_BARRIER barrier{};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = renderTargets[frameIndex].Get();
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrier.Transition.StateBefore = _before;
		barrier.Transition.StateAfter = _after;
		commandList->ResourceBarrier(1, &barrier);
	}

}