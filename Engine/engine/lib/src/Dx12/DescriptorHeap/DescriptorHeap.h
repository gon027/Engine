#pragma once

#include "../Library/Librarys.hpp"
#include "../../../engine/include/Type/Type.hpp"
#include "../include/Fwd.hpp"

namespace engine {

	enum class DescriptorType {
		CSV_SRV_UAV,
		RTV,
		DSV,
		SAMPLER,
		NUM_TYPES
	};

	enum class DescriptorFlag {
		None,
		Visibe
	};

	class DescriptorHeap {
	public:
		DescriptorHeap();
		DescriptorHeap(device_ptr _device, UINT _numDescriptors, DescriptorType _type, DescriptorFlag _flag, UINT _nodeMask = 0);
		~DescriptorHeap() = default;

		bool init(device_ptr _device, UINT _numDescriptors, DescriptorType _type, DescriptorFlag _flag, UINT _nodeMask = 0);

		ID3D12DescriptorHeap* getDescriptorHeap() const;

		u32 getDescriptorSize() const;

		D3D12_CPU_DESCRIPTOR_HANDLE getCpuHandle(u32 _offset = 0) const;

		D3D12_GPU_DESCRIPTOR_HANDLE getGpuHandle(u32 _offset = 0) const;

	private:
		D3D12DescriptorHeap descriptorHeap;
		u32 descriptorSize;
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;
		D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle;
	};

}