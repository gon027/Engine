#include <include/Buffer/Buffer.hpp>
#include "../../include/Library/d3dx12.h"
#include "../../include/EngineCore/EngineCore.hpp"
#include <include/Device/Device.hpp>
#include <include/CommandList/CommandList.hpp>

namespace engine {

	Buffer::Buffer()
		: resource(nullptr)
		, bufferSize()
		, pData(nullptr)
		, isMapping(true)
	{
	}

	Buffer::~Buffer()
	{
		if (resource) {
			resource->Unmap(0, nullptr);
			resource = nullptr;
		}
	}

	bool Buffer::init(const void* _data, size_t _size)
	{

		bufferSize = (_size + 255) & ~255;

		D3D12_HEAP_PROPERTIES prop{
			D3D12_HEAP_TYPE_UPLOAD,
			D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
			D3D12_MEMORY_POOL_UNKNOWN,
			1,
			1
		};

		D3D12_RESOURCE_DESC desc{
			D3D12_RESOURCE_DIMENSION_BUFFER,
			0,
			bufferSize,
			1,
			1,
			1,
			DXGI_FORMAT_UNKNOWN,
			{1, 0},
			D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			D3D12_RESOURCE_FLAG_NONE
		};

		auto hr = EngineDevice()->get()->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(resource.GetAddressOf())
		);

		if (FAILED(hr)) {
			return false;
		}

		map();

		memcpy(pData, _data, _size);

		return true;
	}

	void Buffer::update(const void* _data, size_t _size)
	{
		if (!isMapping) {
			return;
		}

		memcpy(pData, _data, _size);
	}

	void* Buffer::map()
	{
		D3D12_RANGE range{ 0, 0 };
		auto hr = resource->Map(0, &range, reinterpret_cast<void**>(&pData));
		if (FAILED(hr)) {
			return nullptr;
		}

		isMapping = true;

		return pData;
	}

	void Buffer::umMap()
	{
		if (isMapping) {
			resource->Unmap(0, nullptr);
		}
	}

}