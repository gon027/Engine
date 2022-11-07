#pragma once

#include "../../lib/src/Dx12/Library/Librarys.hpp"

#include "../../lib/include/ITexture.hpp"

#include <string>
#include <memory>

#include "../Type/Type.hpp"
#include "../Core/ResourceOption.hpp"

namespace engine {

	class Image;

	class Texture;
	using TexturePtr = std::shared_ptr<Texture>;

	class Texture : public core::ITexture {
	public:
		static TexturePtr create(const std::wstring& _path);

		static TexturePtr create(const Image& _img);

	public:
		Texture();
		~Texture() = default;

		bool loadTexture(const std::wstring& _path);

		bool loadTexture(const u8* _data, u64 _width, u64 _height, u64 _stride);

		u64 getWidth() const {
			return width;
		}

		u64 getHeight() const {
			return height;
		}

		u16 getDepthOrArraySize() const {
			return depthOrArraySize;
		}

		u16 getMipLevels() const {
			return mipLevels;
		}

	private:
		u64 width;
		u64 height;
		u16 depthOrArraySize;
		u16 mipLevels;
		std::shared_ptr<core::ITexture> texture;
	};

}
