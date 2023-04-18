#pragma once

#include <vector>
#include "../Color/Color.hpp"

namespace engine {

	class Image {
	public:
		static Image* WhiteImage(u64 _width = 2, u64 _height = 2);
		static Image* BlackImage(u64 _width = 2, u64 _height = 2);

	public:
		Image();
		Image(u64 _width, u64 _height);
		Image(u64 _width, u64 _height, u8* _data);
		~Image();

		void setPixel(u64 _x, u64 _y, const ColorI& _c);
		void setPixel(u64 _idx, const ColorI& _c);

		u64 getWidth() const {
			return width;
		}

		u64 getHeight() const {
			return height;
		}

		u64 getStride() const {
			return stride;
		}

		u64 getRowPitch() const {
			return rowPitch;
		}

		u64 getSlicePitch() const {
			return slicePitch;
		}

		u8* getData() const {
			return data;
		}

	private:
		u64 width;
		u64 height;
		u64 stride;
		u64 rowPitch;
		u64 slicePitch;
		u8* data;
	};

}