#pragma once

#include <Windows.h>

#include "../Type/Type.hpp"
#include "../Buffer/VertexBuffer.hpp"
#include "../Buffer/IndexBuffer.hpp"
#include "../IndexData/IndexData.hpp"

namespace engine {

	class Mesh {
	public:
		Mesh() : vertexBuffer(), indexBuffer(), indexSize() {};
		~Mesh() = default;

		bool init(const void* _data, UINT _strideInBytes, size_t _dataSize, IndexData& _indexData) {
			/*
			if (!vertexBuffer.init(_data, _strideInBytes, _dataSize)) {
				return false;
			}

			if (!indexBuffer.init(_indexData.getData(), _indexData.getStride(), _indexData.getSize())) {
				return false;
			}

			indexSize = static_cast<u32>(_indexData.getSize());
			*/

			return true;
		}

		void setVertexBuffer(const void* _data, UINT _strideInBytes, size_t _dataSize);

		void setIndexBuffer(IndexData& _indexData);

		void draw();

	private:
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;

		u32 indexSize;
	};

}