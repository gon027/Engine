#include "../../include/Vector/Vector2.h"
#include "../../include/Vector/Vector3.h"
#include <cmath>

namespace gnLib {

	Vector2 Vector2::Up     {  0.0f,  1.0f };
	Vector2 Vector2::Down   {  0.0f, -1.0f };
	Vector2 Vector2::Left   { -1.0f,  0.0f };
	Vector2 Vector2::Right  {  1.0f,  0.0f };
	Vector2 Vector2::One    {  1.0f,  1.0f };
	Vector2 Vector2::Zero   {  0.0f,  0.0f };

	Vector2::Vector2()
		: x(0.0f)
		, y(0.0f)
	{ }

	Vector2::Vector2(const Vector2 & _v)
		: x(_v.x)
		, y(_v.y)	
	{ }

	Vector2::Vector2(float _x, float _y)
		: x(_x)
		, y(_y)
	{ }

	Vector2::Vector2(float _xy)
		: x(_xy)
		, y(_xy)
	{ }

	void Vector2::set(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	void Vector2::set(const Vector2 & _v)
	{
		x = _v.x;
		y = _v.y;
	}

	const float Vector2::length() const
	{
		return std::sqrt(sqrtLength());
	}

	const float Vector2::sqrtLength() const
	{
		return x * x + y * y;
	}

	const Vector2 Vector2::normalized() const
	{
		auto len = length();

		if (len != 0) {
			return { x / len, y / len };
		}
		else {
			return *this;
		}
	}

	const Vector2 Vector2::half() const
	{
		return { x * 0.5f, y * 0.5f };
	}

	const float Vector2::dot(const Vector2& _v)
	{
		return this->x * _v.x + this->y * _v.y;
	}

	const float Vector2::cross(const Vector2 & _v)
	{
		return this->x * _v.y - this->y * _v.x;
	}

	Vector3 Vector2::toVector3()
	{
		return { this->x, this->y, 0.0f };
	}

	const Vector2 Vector2::operator+() const
	{
		return { x, y };
	}

	const Vector2 Vector2::operator-() const
	{
		return { -x, -y };
	}

	const Vector2 Vector2::operator+(const Vector2 & _v) const
	{
		return { x + _v.x, y + _v.y };
	}

	const Vector2 Vector2::operator-(const Vector2 & _v) const
	{
		return { x - _v.x, y - _v.y };
	}

	const Vector2 Vector2::operator*(const Vector2 & _v) const
	{
		return { x * _v.x, y * _v.y };
	}

	const Vector2 Vector2::operator/(const Vector2 & _v) const
	{
		return { x / _v.x, y / _v.y };
	}

	const Vector2& Vector2::operator+=(const Vector2 & _v)
	{
		this->x += _v.x;
		this->y += _v.y;
		return *this;
	}

	const Vector2& Vector2::operator-=(const Vector2 & _v)
	{
		this->x -= _v.x;
		this->y -= _v.y;
		return *this;
	}

	const Vector2& Vector2::operator*=(const Vector2 & _v)
	{
		this->x *= _v.x;
		this->y *= _v.y;
		return *this;
	}

	const Vector2& Vector2::operator/=(const Vector2 & _v)
	{
		this->x /= _v.x;
		this->y /= _v.y;
		return *this; Vector2();
	}

	const bool Vector2::operator==(const Vector2 & _v) const
	{
		return (x == _v.x) && (y == _v.y);
	}

	const bool Vector2::operator!=(const Vector2 & _v) const
	{
		return !(*this == _v);
	}

	const std::string Vector2::toString() const
	{
		return { 
			"[ x: " + std::to_string(x) + 
			", y: " + std::to_string(y) + " ]\n"
		};
	}

	const Vector2 operator*(float _scaler, const Vector2& _v)
	{
		return {
			_scaler * _v.x,
			_scaler * _v.y
		};
	}
}
