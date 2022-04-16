#pragma once

#include "../../include/Library/Librarys.hpp"

namespace engine {

	class DepthStencil {
	public:
		DepthStencil();
		~DepthStencil();

		bool init();

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