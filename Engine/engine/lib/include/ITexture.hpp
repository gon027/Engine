#pragma once

#include <string>
#include "../include/Fwd.hpp"

namespace engine {

	class Image;

	namespace core {

		class ITexture {
		public:
			virtual ~ITexture() = default;

			virtual bool load(device_ptr _device, const std::wstring& _fileName) = 0;

			virtual bool load(device_ptr _device, const Image& _image) = 0;

			virtual unsigned int getWidth() = 0;

			virtual unsigned int getHeight() = 0;
		};

	}

}