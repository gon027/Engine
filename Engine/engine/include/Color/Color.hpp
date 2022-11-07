#pragma once

#include "../Type/Type.hpp"

namespace engine {

	struct ColorF {
		static ColorF Red;
		static ColorF Green;
		static ColorF Blue;
		static ColorF White;
		static ColorF Black;

		ColorF(float _r, float _g, float _b, float _a);
		ColorF(const ColorF& _c);
		~ColorF() = default;

		union {
			float rgba[4];

			struct {
				float r;
				float g;
				float b;
				float a;
			};
		};
	};

	struct ColorI {
		static ColorI Red;
		static ColorI Green;
		static ColorI Blue;
		static ColorI White;
		static ColorI Black;

		ColorI(u8 _r, u8 _g, u8 _b, u8 _a);
		ColorI(unsigned long _color);
		ColorI(const ColorI& _c);
		~ColorI() = default;

		union {
			u8 rgba[4];

			struct {
				u8 r;
				u8 g;
				u8 b;
				u8 a;
			};
		};
	};

}