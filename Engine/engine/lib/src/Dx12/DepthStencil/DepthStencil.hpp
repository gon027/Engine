#pragma once

#include "../Library/Librarys.hpp"
#include "../../../include/DepthStencil.hpp"

namespace engine {

	class Dx12DepthStencil : public core::DepthStencil {
	public:
		Dx12DepthStencil();
		~Dx12DepthStencil();

		bool init(window_ptr _window, device_ptr _device) override;

		void clearDepthStencil();

		inline ID3D12DescriptorHeap* const getDepth() const {
			return descriptorHeap.Get();
		}

	private:
		D3D12DescriptorHeap descriptorHeap;
		UINT descriptorSize;
		D3D12Resource depthStencilResource;
	};

}