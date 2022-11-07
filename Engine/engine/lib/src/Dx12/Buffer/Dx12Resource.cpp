#include "Dx12Resource.hpp"
#include "../Device/Device.hpp"
#include "../Common/Helper.hpp"

namespace engine {

	namespace {

		inline D3D12_HEAP_PROPERTIES toHeapProperties(const HeapType& _type) {
			D3D12_HEAP_PROPERTIES result{};
			result.Type = toHeapType(_type);
			return result;
		}


		inline D3D12_RESOURCE_DESC toResourceDesc(const ResourceDesc& _desc) {
			D3D12_RESOURCE_DESC result{};
			result.Dimension = toResourceDimension(_desc.dimension);
			result.Alignment = 0;
			result.Width = static_cast<UINT64>(_desc.width);
			result.Height = static_cast<UINT>(_desc.height);
			result.DepthOrArraySize = _desc.depthOrArraySize;
			result.MipLevels = _desc.mipLevels;
			result.Format = toFORMAT(_desc.format);
			result.Layout = toLayout(_desc.layout);
			result.SampleDesc.Quality = 0;
			result.SampleDesc.Count = 1;
			return result;
		}
	}

	Dx12Resource::Dx12Resource()
		// : mapData(nullptr)
		: resource(nullptr)
		, resourceType(ResourceType::Upload)
	{
	}

	Dx12Resource::~Dx12Resource()
	{
		if (resource) {
			resource->Release();
			resource = nullptr;
		}
	}

	bool Dx12Resource::init(
		device_ptr _device, const HeapType& _type, const ResourceDesc& _desc,
		ResouceStates _status, const ClearValue* _clearValue)
	{
		assert(_device != nullptr);

		auto* dxDevice = static_cast<Dx12Device*>(_device.get());

		D3D12_HEAP_PROPERTIES prop = toHeapProperties(_type);
		D3D12_RESOURCE_DESC desc = toResourceDesc(_desc);
		HRESULT hr = dxDevice->get()->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			toResourceStates(_status),
			nullptr,
			IID_PPV_ARGS(resource.GetAddressOf())
		);

		return SUCCEEDED(hr);
	}

	bool Dx12Resource::init(
		device_ptr _device, ResourceType _type, const ResourceDesc& _desc,
		ResouceStates _status, const ClearValue* _clearValue
	)
	{
		assert(_device != nullptr);

		auto* device = static_cast<Dx12Device*>(_device.get());

		resourceType = _type;

		D3D12_HEAP_PROPERTIES prop{};
		if (_type == ResourceType::Upload) {
			prop.Type = D3D12_HEAP_TYPE_UPLOAD;
			prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			prop.CreationNodeMask = 1;
			prop.VisibleNodeMask = 1;
		}
		else if (_type == ResourceType::DepthStencil) {
			prop.Type = D3D12_HEAP_TYPE_DEFAULT;
		}
		else if (_type == ResourceType::ShaderResource) {
			prop.Type = D3D12_HEAP_TYPE_CUSTOM;
			prop.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
			prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
			prop.CreationNodeMask = 0;
			prop.VisibleNodeMask = 0;
		}
		else if (_type == ResourceType::UnorderedAccess) {
			// prop.Type == D3D12_HEAP_TYPE_UPLOAD;
		}

		D3D12_RESOURCE_DESC desc{};
		desc.Dimension = toResourceDimension(_desc.dimension);
		desc.Alignment = 0;
		desc.Width     = static_cast<UINT64>(_desc.width);
		desc.Height    = static_cast<UINT>(_desc.height);
		desc.DepthOrArraySize = _desc.depthOrArraySize;
		desc.MipLevels = _desc.mipLevels;
		desc.Format = toFORMAT(_desc.format);
		desc.Layout = toLayout(_desc.layout);
		desc.SampleDesc.Quality = 0;
		desc.SampleDesc.Count = 1;

		auto resourceStates = toResourceStates(_status);
		HRESULT hr = device->get()->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			resourceStates,
			nullptr,
			IID_PPV_ARGS(resource.GetAddressOf())
		);

		return SUCCEEDED(hr);
	}

	bool Dx12Resource::writeToSubResource(const void* _data, u64 _width, u64 _height, u64 _rowPitch, u64 _slicePitch)
	{
		D3D12_BOX box{ 0, 0, 0, (u32)_width, (u32)_height, 1 };
		HRESULT hr = resource->WriteToSubresource(
			0,
			nullptr, // &box,
			_data,
			static_cast<UINT>(_rowPitch),
			static_cast<UINT>(_slicePitch)
		);

		if (FAILED(hr)) {
			return false;
		}

		return true;
	}

	void* Dx12Resource::map()
	{
		if (resourceType == ResourceType::ShaderResource) {
			D3D12_RANGE range{ 0, 0 };
			HRESULT hr = resource->Map(0, &range, nullptr);
			if (FAILED(hr)) {
				return nullptr;
			}

			return nullptr;
		}

		u8* pData{ nullptr };
		D3D12_RANGE range{ 0, 0 };
		HRESULT hr = resource->Map(0, &range, reinterpret_cast<void**>(&pData));
		if (FAILED(hr)) {
			return nullptr;
		}

		return pData;
	}

	void Dx12Resource::unMap()
	{
		resource->Unmap(0, nullptr);
	}
}
