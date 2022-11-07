#include "Dx12CommandList.hpp"
#include "../Device/Device.hpp"

#include "../SwapChain/Dx12SwapChain.hpp"
#include "../DepthStencil/DepthStencil.hpp"
#include "../RootSignature/RootSignature.hpp"
#include "../PipelineState/PipelineState.hpp"

#include "../Buffer/Dx12Resource.hpp"
#include "../../include/Buffer/VertexBuffer.hpp"
#include "../../include/Buffer/IndexBuffer.hpp"
#include "../../include/Buffer/ConstantBuffer.hpp"

#include "../Texture/Dx12Texture.hpp"

#include "../Common/Helper.hpp"

namespace engine {

	Dx12CommandList::Dx12CommandList()
		: commandList(nullptr)
		, commandAllocator(nullptr)
		, device(nullptr)
	{
	}

	Dx12CommandList::~Dx12CommandList()
	{
		OutputDebugString("Dx12CommandList destructor called. \n");
	}

	bool Dx12CommandList::init(device_ptr _device)
	{
		assert(_device != nullptr);

		//  device = static_cast<Dx12Device*>(_device.get())->get();
		device = std::dynamic_pointer_cast<Dx12Device>(_device);

		HRESULT hr{};

		// Command Allocator
		hr = device->get()->CreateCommandAllocator(
			D3D12_COMMAND_LIST_TYPE_DIRECT,
			IID_PPV_ARGS(commandAllocator.GetAddressOf())
		);

		if (FAILED(hr)) {
			return false;
		}

		// Command List
		hr = device->get()->CreateCommandList(
			0,
			D3D12_COMMAND_LIST_TYPE_DIRECT,
			commandAllocator.Get(),
			nullptr,
			IID_PPV_ARGS(commandList.GetAddressOf())
		);

		if (FAILED(hr)) {
			return false;
		}

		close();

		return true;
	}

	void Dx12CommandList::reset()
	{
		commandAllocator->Reset();

		commandList->Reset(commandAllocator.Get(), nullptr);
	}

	void Dx12CommandList::close()
	{
		commandList->Close();
	}

	void Dx12CommandList::setViewport(const ViewPort& _viewport)
	{
		D3D12_VIEWPORT viewport{};
		viewport.TopLeftX = _viewport.topLeftX;
		viewport.TopLeftY = _viewport.topLeftY;
		viewport.Width    = _viewport.width;
		viewport.Height   = _viewport.height;
		viewport.MinDepth = _viewport.minDepth;
		viewport.MaxDepth = _viewport.maxDepth;
		commandList->RSSetViewports(1, &viewport);
	}

	void Dx12CommandList::setScissorRect(const ScissorRect& _scissorRect)
	{
		D3D12_RECT scissorRect{};
		scissorRect.top    = _scissorRect.top;
		scissorRect.left   = _scissorRect.left;
		scissorRect.right  = _scissorRect.right;
		scissorRect.bottom = _scissorRect.bottom;
		commandList->RSSetScissorRects(1, &scissorRect);
	}

	void Dx12CommandList::resourceBarrier(
		core::swapChain_ptr _swapChain, ResouceStates _before, ResouceStates _after)
	{
		D3D12_RESOURCE_BARRIER barrier{};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

		ID3D12Resource* resource = static_cast<Dx12SwapChain*>(_swapChain.get())->getCurrentResource();
		barrier.Transition.pResource = resource;
		barrier.Transition.StateBefore = toResourceStates(_before);
		barrier.Transition.StateAfter = toResourceStates(_after);

		commandList->ResourceBarrier(1, &barrier);

	}

	void Dx12CommandList::clearRenderTargetView(core::swapChain_ptr _swapChain, const ColorF& _color)
	{
		auto handle = static_cast<Dx12SwapChain*>(_swapChain.get())->getCurrenrHandle();
		commandList->ClearRenderTargetView(handle, _color.rgba, 0, nullptr);
	}

	void Dx12CommandList::setRenderTargets(core::swapChain_ptr _swapChain, core::depthStencil_ptr _depthStencil)
	{
		auto handle = static_cast<Dx12SwapChain*>(_swapChain.get())->getCurrenrHandle();
		auto descriptor = static_cast<Dx12DepthStencil*>(_depthStencil.get())->getDepth()->GetCPUDescriptorHandleForHeapStart();
		commandList->OMSetRenderTargets(1, &handle, 0, &descriptor);
	}

	void Dx12CommandList::clearDepthStencilView(core::depthStencil_ptr _depthStencil)
	{
		auto cpuHandle = static_cast<Dx12DepthStencil*>(_depthStencil.get())->getDepth()->GetCPUDescriptorHandleForHeapStart();

		// 深度ステンシルビューをクリア
		commandList->ClearDepthStencilView(
			cpuHandle,
			D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
			1.0f,
			0,
			0,
			nullptr
		);

		commandList->OMSetStencilRef(0);
	}

	void Dx12CommandList::setRootSignature(const engine::RootSignature& _rootSignature)
	{
		commandList->SetGraphicsRootSignature(_rootSignature.get());
	}

	void Dx12CommandList::setPipelineState(core::pipeline_ptr _pipelineState)
	{
		assert(_pipelineState != nullptr);

		auto* pipeline = static_cast<PipelineState*>(_pipelineState.get());
		commandList->SetPipelineState(pipeline->get());
	}

	void Dx12CommandList::setPrimitiveTopology()
	{
		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void Dx12CommandList::setConstantBuffer(ConstantBuffer& _buffer, unsigned int _index)
	{
		auto resource = _buffer.get();
		auto dx = static_cast<Dx12Resource*>(resource.get());

		commandList->SetGraphicsRootConstantBufferView(_index, dx->get()->GetGPUVirtualAddress());
	}

	void Dx12CommandList::setVertexBuffer(VertexBuffer& _buffer)
	{
		auto resource = _buffer.get();
		auto dx = static_cast<Dx12Resource*>(resource.get());

		D3D12_VERTEX_BUFFER_VIEW view{};
		view.BufferLocation = dx->get()->GetGPUVirtualAddress();
		view.StrideInBytes = static_cast<UINT>(_buffer.getStride());
		view.SizeInBytes = static_cast<UINT>(_buffer.getBufferSize());

		commandList->IASetVertexBuffers(0, 1, &view);
	}

	void Dx12CommandList::setIndexBuffer(IndexBuffer& _buffer)
	{
		auto resource = _buffer.get();
		auto dx = static_cast<Dx12Resource*>(resource.get());

		D3D12_INDEX_BUFFER_VIEW view{};
		view.BufferLocation = dx->get()->GetGPUVirtualAddress();
		view.SizeInBytes = static_cast<UINT>(_buffer.getBufferSize());
		view.Format = DXGI_FORMAT_R32_UINT;

		commandList->IASetIndexBuffer(&view);
		commandList->DrawIndexedInstanced((UINT)_buffer.getBufferSize(), 1, 0, 0, 0);
	}

	void Dx12CommandList::setTexture(core::ITexture* _texture, u64 _slot)
	{
		assert(_texture != nullptr);
		auto* dx12Texture = static_cast<Dx12Texture*>(_texture);

		ID3D12DescriptorHeap* heaps[]{ dx12Texture->getHeap() };
		auto gpuHandle = dx12Texture->getHeap()->GetGPUDescriptorHandleForHeapStart();
		commandList->SetDescriptorHeaps(_countof(heaps), heaps);
		commandList->SetGraphicsRootDescriptorTable((UINT)_slot, gpuHandle);
	}

	void Dx12CommandList::setTexture(texture_ptr _texture, u64 _slot)
	{
		assert(_texture != nullptr);
		auto dx12Texture = std::dynamic_pointer_cast<Dx12Texture>(_texture);

		ID3D12DescriptorHeap* heaps[]{ dx12Texture->getHeap() };
		auto gpuHandle = dx12Texture->getHeap()->GetGPUDescriptorHandleForHeapStart();
		commandList->SetDescriptorHeaps(_countof(heaps), heaps);
		commandList->SetGraphicsRootDescriptorTable((UINT)_slot, gpuHandle);
	}

	void Dx12CommandList::setDescriptorHeaps(u64 _count, ID3D12DescriptorHeap* const* _heaps)
	{
		commandList->SetDescriptorHeaps((UINT)_count, _heaps);
	}

	void Dx12CommandList::setGraphicsRootDescriptorTable(u64 _parameterIndex, D3D12_GPU_DESCRIPTOR_HANDLE _handle)
	{
		commandList->SetGraphicsRootDescriptorTable((UINT)_parameterIndex, _handle);
	}

	std::shared_ptr<core::ICommandList> createCommandList() {
		return std::shared_ptr<Dx12CommandList> {
			new Dx12CommandList{}
		};
	}

}