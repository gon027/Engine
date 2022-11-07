#pragma once

#include <vector>
#include "../Type/Type.hpp"

namespace engine {

	class IndexData {
	public:
		IndexData() : indexes(), indexSize(0) {};
		~IndexData() = default;

		void setTriangle(u32 _p1, u32 _p2, u32 _p3) {
			indexes.push_back(_p1);
			indexes.push_back(_p2);
			indexes.push_back(_p3);

			indexSize += 3;
		}

		size_t getSize() const {
			return indexSize;
		}

		size_t getStride() const {
			return sizeof(u32);
		}

		u32* getData() {
			return indexes.data();
		}

		u32 operator[](size_t _index) {
			return indexes[_index];
		}

	private:
		std::vector<u32> indexes;
		size_t indexSize;
	};

}