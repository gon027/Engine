#pragma once

#include "../Library/Librarys.hpp"
#include "../include/Fwd.hpp"
#include "../include/ICommandList.hpp"

namespace engine {

	class Dx12CommandList : public core::ICommandList {
	public:
		Dx12CommandList();
		~Dx12CommandList();

		bool init(device_ptr _device) override;

		void reset() override;

		void close() override;

		void setViewport(const ViewPort& _viewport) override;

		void setScissorRect(const ScissorRect& _scissorRect) override;

		void resourceBarrier(
			core::swapChain_ptr _swapChain, ResouceStates _before, ResouceStates _after
		) override;

		void clearRenderTargetView(core::swapChain_ptr _swapChain, const ColorF& _color) override;

		void setRenderTargets(core::swapChain_ptr _swapChain, core::depthStencil_ptr _depthStencil) override;

		void clearDepthStencilView(core::depthStencil_ptr _depthStencil) override;

		void setRootSignature(const engine::RootSignature& _rootSignature) override;

		void setPipelineState(core::pipeline_ptr _pipelineState) override;

		void setPrimitiveTopology() override;

		void setConstantBuffer(ConstantBuffer& _buffer, unsigned int _index);

		void setVertexBuffer(VertexBuffer& _buffer) override;

		void setIndexBuffer(IndexBuffer& _buffer) override;

		void setTexture(core::ITexture* _texture, u64 _slot) override;

		void setTexture(texture_ptr _texture, u64 _slot) override;

		void setDescriptorHeaps(u64 _count, ID3D12DescriptorHeap* const* _heaps) override;

		void setGraphicsRootDescriptorTable(u64 _parameterIndex, D3D12_GPU_DESCRIPTOR_HANDLE _handle) override;

		void drawIndexedInstanced(u64 a, u64 b, u64 c, u64 d, u64 e) override;

		inline ID3D12GraphicsCommandList* const get() const {
			return commandList.Get();
		}

	private:
		D3D12CommandList commandList;
		D3D12CommandAllocator commandAllocator;

	private:
		//ID3D12Device* device;
		std::shared_ptr<class Dx12Device> device;
	};

}