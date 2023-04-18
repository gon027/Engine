#include "..\..\include\Image\Image.hpp"

namespace engine {

	Image::Image()
		: width(0)
		, height(0)
		, stride(sizeof(ColorI))
		, rowPitch(width* stride)
		, slicePitch(width* stride* height)
		, data(0)
	{}

	Image::Image(u64 _width, u64 _height)
		: width(_width)
		, height(_height)
		, stride(sizeof(ColorI))
		, rowPitch(width* stride)
		, slicePitch(width* stride* height)
		, data(new u8[width * stride * height])
	{
		for (size_t y{ 0 }; y < height; ++y) {
			for (size_t x{ 0 }; x < rowPitch; x += stride) {
				setPixel(x, y, ColorI::White);
			}
		}
	}

	Image::Image(u64 _width, u64 _height, u8* _data)
		: width(_width)
		, height(_height)
		, stride(sizeof(ColorI))
		, rowPitch(width* stride)
		, slicePitch(width* stride* height)
		, data(_data)
	{}

	Image::~Image() {
		if (data) {
			delete[] data;
			data = nullptr;
		}
	}

	void Image::setPixel(u64 _x, u64 _y, const ColorI& _c) {
		auto idx = _y * rowPitch + _x;
		data[idx + 0UL] = _c.r;
		data[idx + 1UL] = _c.g;
		data[idx + 2UL] = _c.b;
		data[idx + 3UL] = _c.a;
	}

	void Image::setPixel(u64 _idx, const ColorI& _c) {
		memcpy(data + _idx, _c.rgba, sizeof(_c.rgba));
	}
}