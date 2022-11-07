#include "../../include/Color/Color.hpp"

namespace engine {

	ColorF ColorF::Red   = { 1.0f, 0.0f, 0.0f, 0.0f };
	ColorF ColorF::Green = { 0.0f, 1.0f, 0.0f, 1.0f };
	ColorF ColorF::Blue  = { 0.0f, 0.0f, 1.0f, 1.0f };
	ColorF ColorF::White = { 1.0f, 1.0f, 1.0f, 1.0f };
	ColorF ColorF::Black = { 0.0f, 0.0f, 0.0f, 0.0f };

	ColorF::ColorF(float _r, float _g, float _b, float _a)
		: r(_r)
		, g(_g)
		, b(_b)
		, a(_a)
	{
	}

	ColorF::ColorF(const ColorF& _c)
		: r(_c.r)
		, g(_c.g)
		, b(_c.b)
		, a(_c.a)
	{
	}

	ColorI ColorI::Red   = { 0xFF, 0, 0, 0xFF };
	ColorI ColorI::Green = { 0, 0xFF, 0, 0xFF };
	ColorI ColorI::Blue  = { 0, 0, 0xFF, 0xFF };
	ColorI ColorI::White = { 0xFF, 0xFF, 0xFF, 0xFF };
	ColorI ColorI::Black = { 0, 0, 0, 0 };

	ColorI::ColorI(u8 _r, u8 _g, u8 _b, u8 _a)
		: r(_r)
		, g(_g)
		, b(_b)
		, a(_a)
	{
	}

	ColorI::ColorI(unsigned long _color)
		: a((_color >> 24))
		, r((_color >> 16))
		, g((_color >> 8))
		, b((_color  ))
	{
	}

	ColorI::ColorI(const ColorI& _c)
		: r(_c.r)
		, g(_c.g)
		, b(_c.b)
		, a(_c.a)
	{
	}

}