#pragma once

#include <vector>

#include "../../include/Library/Librarys.hpp"
#include "../../include/Type/Type.hpp"

namespace engine {

	class VertexBuffer {
	public:
		VertexBuffer();
		~VertexBuffer();

		bool init(const void* _data, UINT _strideInBytes, size_t _dataSize);

		void copyBuffer(const void* _data);

		inline D3D12_VERTEX_BUFFER_VIEW& getView() {
			return view;
		}

	private:
		D3D12Resource resource;
		u32 bufferSize;
		D3D12_VERTEX_BUFFER_VIEW view;
	};

}