#pragma once

#include <vector>
#include "../Color/Color.hpp"

namespace engine {

	class Image {
	public:
		Image()
			: width(0)
			, height(0)
			, stride(sizeof(ColorI))
			, rowPitch(width * stride)
			, slicePitch(width * stride * height)
			, data(0)
		{}
		Image(u64 _width, u64 _height)
			: width(_width)
			, height(_height)
			, stride(sizeof(ColorI))
			, rowPitch(width* stride)
			, slicePitch(width* stride* height)
			, data(new u8[width * stride * height])
		{
			for (size_t y{ 0 }; y < height; ++y) {
				for (size_t x{ 0 }; x < rowPitch; x += stride) {
					setPixel(x, y, ColorI::Green);
				}
			}
		}
		Image(u8* _data, u64 _width, u64 _height)
			: width(_width)
			, height(_height)
			, stride(sizeof(ColorI))
			, rowPitch(width* stride)
			, slicePitch(width* stride* height)
			, data(_data)
		{}
		
		~Image() {
			if (data) {
				delete[] data;
				data = nullptr;
			}
		};

		void setPixel(u64 _x, u64 _y, const ColorI& _c) {
			//auto idx = _y * stride * width + _x;
			// memcpy(data.data(), _c.rgba, sizeof(ColorI));

			auto idx = _y * rowPitch + _x;
			data[idx + 0UL] = _c.r;
			data[idx + 1UL] = _c.g;
			data[idx + 2UL] = _c.b;
			data[idx + 3UL] = _c.a;
		}

		void setPixel(u64 _idx, const ColorI& _c) {
			memcpy(data + _idx, _c.rgba, sizeof(_c.rgba));
		}

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