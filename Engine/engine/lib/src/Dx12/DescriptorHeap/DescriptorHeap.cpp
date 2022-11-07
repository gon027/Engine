#include "DescriptorHeap.h"
#include "../Device/Device.hpp"

namespace engine {

	namespace {

		D3D12_DESCRIPTOR_HEAP_TYPE toHeapType(DescriptorType _type) {
			switch (_type)
			{
			case engine::DescriptorType::CSV_SRV_UAV:
				return D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			case engine::DescriptorType::RTV:
				return D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			case engine::DescriptorType::DSV:
				return D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
			case engine::DescriptorType::SAMPLER:
				return D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
			case engine::DescriptorType::NUM_TYPES:
				return D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES;
			default:
				return D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			}
		}

		D3D12_DESCRIPTOR_HEAP_FLAGS toHeapFlag(DescriptorFlag _flag) {
			switch (_flag)
			{
			case engine::DescriptorFlag::None:
				return D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			case engine::DescriptorFlag::Visibe:
				return D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
			default:
				return D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			}
		}
	}

	DescriptorHeap::DescriptorHeap()
		: descriptorHeap(nullptr)
		, descriptorSize(0)
		, cpuHandle({})
		, gpuHandle({})
	{
	}

	DescriptorHeap::DescriptorHeap(device_ptr _device, UINT _numDescriptors, DescriptorType _type, DescriptorFlag _flag, UINT _nodeMask)
		: descriptorHeap(nullptr)
		, descriptorSize(0)
		, cpuHandle({})
		, gpuHandle({})
	{
		assert(_device != nullptr);

		auto* device = static_cast<Dx12Device*>(_device.get());

		D3D12_DESCRIPTOR_HEAP_DESC desc{};
		desc.NumDescriptors = _numDescriptors;
		desc.NodeMask = _nodeMask;
		desc.Type = toHeapType(_type);
		desc.Flags = toHeapFlag(_flag);

		HRESULT hr = device->get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(descriptorHeap.GetAddressOf()));
		if (FAILED(hr)) {
			return;
		}

		descriptorSize = device->get()->GetDescriptorHandleIncrementSize(desc.Type);
		cpuHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
		gpuHandle = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
	}

	bool DescriptorHeap::init(device_ptr _device, UINT _numDescriptors, DescriptorType _type, DescriptorFlag _flag, UINT _nodeMask)
	{
		assert(_device != nullptr);

		auto* device = static_cast<Dx12Device*>(_device.get());

		D3D12_DESCRIPTOR_HEAP_DESC desc{};
		desc.NumDescriptors = _numDescriptors;
		desc.NodeMask = _nodeMask;
		desc.Type = toHeapType(_type);
		desc.Flags = toHeapFlag(_flag);

		HRESULT hr = device->get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(descriptorHeap.GetAddressOf()));
		if (FAILED(hr)) {
			return false;
		}
		
		descriptorSize = device->get()->GetDescriptorHandleIncrementSize(desc.Type);
		cpuHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
		gpuHandle = descriptorHeap->GetGPUDescriptorHandleForHeapStart();

		return true;
	}

	ID3D12DescriptorHeap* DescriptorHeap::getDescriptorHeap() const
	{
		return descriptorHeap.Get();
	}

	u32 DescriptorHeap::getDescriptorSize() const
	{
		return descriptorSize;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::getCpuHandle(u32 _offset) const
	{
		auto handle = cpuHandle;
		handle.ptr += static_cast<SIZE_T>( _offset) * static_cast<SIZE_T>(getDescriptorSize());
		return handle;
	}

	D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeap::getGpuHandle(u32 _offset) const
	{
		auto handle = gpuHandle;
		handle.ptr += static_cast<SIZE_T>(_offset) * static_cast<SIZE_T>(getDescriptorSize());;
		return handle;
	}
}