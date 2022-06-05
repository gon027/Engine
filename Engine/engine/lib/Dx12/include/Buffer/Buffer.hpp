#pragma once

#include <include/Library/Librarys.hpp>
#include <include/Type/Type.hpp>

namespace engine {

	enum class BufferType {
		Custum,
		Default,
		ReadBack,
		Upload
	};

	class Buffer {
	public:
		Buffer();
		~Buffer();

		bool init(const void* _data, size_t _size);

		void update(const void* _data, size_t _size);

		void* map();

		void umMap();

		D3D12_GPU_VIRTUAL_ADDRESS getGpuVirtualAddress() const {
			return resource->GetGPUVirtualAddress();
		}

		ID3D12Resource* getResource() const {
			return resource.Get();
		}

	private:
		D3D12Resource resource;
		u32 bufferSize;
		u8* pData;
		bool isMapping;
	};

}