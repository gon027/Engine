#include "../../include/Graphics/IndexBuffer.hpp"
#include "../../include/Library/d3dx12.h"
#include "../../include/EngineCore/EngineCore.hpp"
#include "../../include/Graphics/Device.hpp"

namespace engine {

	IndexBuffer::IndexBuffer()
		: resource(nullptr)
		, bufferSize(0)
		, view()
	{
	}

	IndexBuffer::~IndexBuffer()
	{
	}

	bool IndexBuffer::init(const void* _data, u32 _strideInBytes, size_t _dataSize)
	{
		bufferSize = _strideInBytes * static_cast<u32>(_dataSize);

		CD3DX12_HEAP_PROPERTIES prop{ D3D12_HEAP_TYPE_UPLOAD };
		D3D12_RESOURCE_DESC desc{ CD3DX12_RESOURCE_DESC::Buffer(bufferSize) };
		HRESULT hr = EngineDevice()->get()->CreateCommittedResource(
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

		copyBuffer(_data);

		view.BufferLocation = resource->GetGPUVirtualAddress();
		view.SizeInBytes = bufferSize;
		view.Format = DXGI_FORMAT_R32_UINT;

		return true;
	}

	void IndexBuffer::copyBuffer(const void* _data)
	{
		u32* pData = nullptr;
		CD3DX12_RANGE range{ 0, 0 };
		auto hr = resource->Map(0, &range, reinterpret_cast<void**>(&pData));
		{
			if (FAILED(hr)) {
				return;
			}

			memcpy(pData, _data, bufferSize);
			resource->Unmap(0, nullptr);
		}
	}

}