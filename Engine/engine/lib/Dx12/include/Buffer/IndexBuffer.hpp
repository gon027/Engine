#pragma once

#include <vector>

#include <include/Library/Librarys.hpp>
#include <include/Type/Type.hpp>

namespace engine {

	class IndexBuffer {
	public:
		IndexBuffer();
		~IndexBuffer();

		bool init(const void* _data, u32 _strideInBytes, size_t _dataSize);

		void copyBuffer(const void* _data);

		inline u32 getBufferSize() const {
			return bufferSize;
		}

		inline D3D12_INDEX_BUFFER_VIEW& getView() {
			return view;
		}

	private:
		D3D12Resource resource;
		u32 bufferSize;

		D3D12_INDEX_BUFFER_VIEW view;
	};

}