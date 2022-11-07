#pragma once

#include "Vec.hpp"

namespace engine {

	struct Vertex2D {
	public:
		Vertex2D()
			: position({ 0.0f, 0.0f, 0.0f })
			, color({ 1.0f, 1.0f, 1.0f, 1.0f })
			, uv({ 0.0f, 0.0f })
		{}

		Vertex2D(const Vec3& _position, const Vec4& _color, const Vec2& _uv)
			: position(_position)
			, color(_color)
			, uv(_uv)
		{}

		~Vertex2D() = default;

	public:
		Vec3 position;
		Vec4 color;
		Vec2 uv;
	};

	struct Vertex2DColor {
	public:
		Vertex2DColor()
			: position({ 0.0f, 0.0f, 0.0f })
			, color({ 1.0f, 1.0f, 1.0f, 1.0f })
		{}

		Vertex2DColor(const Vec3& _position, const Vec4& _color)
			: position(_position)
			, color(_color)
		{}

		~Vertex2DColor() = default;

	public:
		Vec3 position;
		Vec4 color;
	};

	struct Vertex2DTexture {
	public:
		Vertex2DTexture()
			: position({ 0.0f, 0.0f, 0.0f })
			, uv({ 0.0f, 0.0f })
		{}

		Vertex2DTexture(const Vec3& _position, const Vec2& _uv)
			: position(_position)
			, uv(_uv)
		{}

		~Vertex2DTexture() = default;

	public:
		Vec3 position;
		Vec2 uv;
	};

}