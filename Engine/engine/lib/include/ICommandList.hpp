#pragma once

#include <memory>
#include "ViewPort.hpp"
#include "ScissorRect.hpp"
#include "../../../engine/include/Core/ResourceOption.hpp"
#include "../../../engine/include/Color/Color.hpp"
#include "../src/Dx12/Library/Librarys.hpp"

namespace engine {

	class RootSignature;

	class ConstantBuffer;
	class VertexBuffer;
	class IndexBuffer;

	namespace core {

		// Todo: Ç¢Ç∏ÇÍè¡Ç∑Ç©Ç‡
		class DepthStencil;

		class Pipeline;

		using swapChain_ptr = std::shared_ptr<ISwapChain>;
		using depthStencil_ptr = std::shared_ptr<DepthStencil>;
		using pipeline_ptr = std::shared_ptr<Pipeline>;

		class ICommandList {
		public:
			virtual ~ICommandList() = default;

			virtual bool init(device_ptr _device) = 0;

			virtual void close() = 0;

			virtual void reset() = 0;

			virtual void setViewport(const ViewPort& _viewport) = 0;

			virtual void setScissorRect(const ScissorRect& _scissorRect) = 0;

			virtual void resourceBarrier(swapChain_ptr _swapChain, ResouceStates _before, ResouceStates _after) = 0;

			virtual void clearRenderTargetView(swapChain_ptr _swapChain, const ColorF& _color) = 0;

			virtual void setRenderTargets(swapChain_ptr _swapChain, depthStencil_ptr _depthStencil) = 0;

			virtual void clearDepthStencilView(depthStencil_ptr _depthStencil) = 0;

			virtual void setRootSignature(const engine::RootSignature& _rootSignature) = 0;

			virtual void setPipelineState(pipeline_ptr _pipelineState) = 0;

			virtual void setPrimitiveTopology() = 0;

			virtual void setConstantBuffer(ConstantBuffer& _buffer, unsigned int _index) = 0;

			virtual void setVertexBuffer(VertexBuffer& _buffer) = 0;

			virtual void setIndexBuffer(IndexBuffer& _buffer) = 0;

			virtual void setTexture(ITexture* _texture, u64 _slot) = 0;

			virtual void setTexture(texture_ptr _texture, u64 _slot) = 0;

			virtual void setDescriptorHeaps(u64 _count, ID3D12DescriptorHeap* const *  _heaps) = 0;

			virtual void setGraphicsRootDescriptorTable(u64 _parameterIndex, D3D12_GPU_DESCRIPTOR_HANDLE _handle) = 0;

			virtual void drawIndexedInstanced(u64 a, u64 b, u64 c, u64 d, u64 e) = 0;

		};

	}

	std::shared_ptr<core::ICommandList> createCommandList();

}