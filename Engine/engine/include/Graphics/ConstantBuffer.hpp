#pragma once

#include "../../include/Library/Librarys.hpp"
#include "../../include/Type/Type.hpp"

namespace engine {

	class ConstantBuffer {
	public:
		ConstantBuffer();
		~ConstantBuffer();

		bool init(const void* _data, size_t _size);

		void setConstantBuffer(unsigned int _index, const void* _data);

		inline u8* getData() const {
			return pData;
		}

		inline u32 getBufferSize() const {
			return bufferSize;
		}

		inline D3D12_GPU_VIRTUAL_ADDRESS getGPUVirtualAddress() const {
			return resource->GetGPUVirtualAddress();
		}

		inline ID3D12Resource* const get() const {
			return resource.Get();
		}

	private:
		D3D12Resource resource;
		u8* pData;
		u32 bufferSize;
	};

}