#pragma once

#include "../Core/Resource.h"
#include "../Type/Type.hpp"

namespace engine {

	namespace core {
		class IDevice;
	}

	using device_ptr = std::shared_ptr<core::IDevice>;

	class ConstantBuffer {
	public:
		ConstantBuffer();
		~ConstantBuffer();

		bool init(device_ptr _device, const void* _data, size_t _size);

		void update(const void* _data, size_t _size);

		u64 getBufferSize() const;

		resource_ptr get() const;

	private:
		resource_ptr resource;
		void* pData;
		u64 bufferSize;
	};
}