#pragma once

#include "../Core/Resource.h"
#include "../Type/Type.hpp"

namespace engine {

	namespace core {
		class IDevice;
	}

	using device_ptr = std::shared_ptr<core::IDevice>;

	class IndexBuffer {
	public:
		IndexBuffer();
		~IndexBuffer();

		bool init(device_ptr _device, const void* _data, u64 _stride, size_t _size);

		void update(const void* _data, u64 _stride, size_t _size);

		u64 getStride() const;

		u64 getSize() const;

		u64 getBufferSize() const;

		resource_ptr get() const;

	private:
		resource_ptr resource;
		u64 stride;
		u64 size;
		u64 bufferSize;
	};

}