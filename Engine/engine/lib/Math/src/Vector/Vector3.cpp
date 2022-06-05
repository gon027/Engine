#include "../../include/Vector/Vector2.h"
#include "../../include/Vector/Vector3.h"
#include <cmath>

namespace gnLib {

	Vector3 Vector3::Up      { 0.0f, 1.0f, 0.0f  };
	Vector3 Vector3::Down    { 0.0f, -1.0f, 0.0f };
	Vector3 Vector3::Left    { -1.0f, 0.0f, 0.0f };
	Vector3 Vector3::Right   { 1.0f, 0.0f, 0.0f  };
	Vector3 Vector3::Back    { 0.0f, 0.0f, -1.0f };
	Vector3 Vector3::Forward { 0.0f, 0.0f, 1.0f  };
	Vector3 Vector3::One     { 1.0f, 1.0f, 1.0f  };
	Vector3 Vector3::Zero    { 0.0f, 0.0f, 0.0f  };

	Vector3::Vector3()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{ }

	Vector3::Vector3(const Vector2 & _v)
		: x(_v.x)
		, y(_v.y)
		, z(0.0f)
	{ }

	Vector3::Vector3(const Vector3 & _v)
		: x(_v.x)
		, y(_v.y)
		, z(_v.z)
	{ }

	gnLib::Vector3::Vector3(float _x, float _y, float _z)
		: x(_x)
		, y(_y)
		, z(_z)
	{ }

	gnLib::Vector3::Vector3(float _xyz)
		: x(_xyz)
		, y(_xyz)
		, z(_xyz)
	{ }

	void Vector3::set(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	void Vector3::set(const Vector3 & _v)
	{
		set(_v.x, _v.y, _v.z);
	}

	const float Vector3::length() const
	{
		return sqrtf(sqrtLength());
	}

	const float Vector3::sqrtLength() const
	{
		return x * x + y * y + z * z;
	}

	const Vector3 Vector3::normalized() const
	{
		auto len = length();
		auto oneOverLen = 1.0f / len;

		return {
			x * oneOverLen,
			y * oneOverLen,
			z * oneOverLen
		};
	}

	const Vector3 Vector3::half() const
	{
		return { x * 0.5f, y * 0.5f, z * 0.5f };
	}

	const float Vector3::dot(const Vector3 & _v) const
	{
		return x * _v.x + y * _v.y + z * _v.z;
	}

	const Vector3 Vector3::cross(const Vector3 & _v) const
	{
		return {
			y * _v.z - _v.y * z,
			-(x * _v.z - z * _v.x),
			x * _v.y - y * _v.x
		};
	}

	const Vector2 Vector3::toVector2()
	{
		return { x, y };
	}

	const Vector3 Vector3::operator+() const
	{
		return { x, y, z };
	}

	const Vector3 Vector3::operator-() const
	{
		return { -x, -y, -z };
	}

	const Vector3 Vector3::operator+(const Vector3 & _v) const
	{
		return { x + _v.x, y + _v.y, z + _v.z };
	}

	const Vector3 Vector3::operator-(const Vector3 & _v) const
	{
		return { x - _v.x, y - _v.y, z - _v.z };
	}

	const Vector3 Vector3::operator*(const Vector3 & _v) const
	{
		return { x * _v.x, y * _v.y, z * _v.z };
	}

	const Vector3 Vector3::operator/(const Vector3 & _v) const
	{
		return { x / _v.x, y / _v.y, z / _v.z };
	}

	const Vector3& Vector3::operator+=(const Vector3 & _v)
	{
		this->x += _v.x;
		this->y += _v.y;
		this->z += _v.z;
		return *this;
	}

	const Vector3& Vector3::operator-=(const Vector3 & _v)
	{
		this->x -= _v.x;
		this->y -= _v.y;
		this->z -= _v.z;
		return *this;
	}

	const Vector3& Vector3::operator*=(const Vector3 & _v)
	{
		this->x *= _v.x;
		this->y *= _v.y;
		this->z *= _v.z;
		return *this;
	}

	const Vector3& Vector3::operator/=(const Vector3 & _v)
	{
		this->x /= _v.x;
		this->y /= _v.y;
		this->z /= _v.z;
		return *this;
	}

	const bool Vector3::operator==(const Vector3 & _v) const
	{
		return (x == _v.x) && (y == _v.y) && (z == _v.z);
	}

	const bool Vector3::operator!=(const Vector3 & _v) const
	{
		return !(*this == _v);
	}

	const std::string Vector3::toString() const 
	{
		return { 
			" [x: " + std::to_string(x) + 
			", y: " + std::to_string(y) + 
			", z: " + std::to_string(z) + "]\n"
		};
	}

	const Vector3 operator*(float _scaler, const Vector3 _v)
	{
		return {
			_scaler * _v.x,
			_scaler * _v.y,
			_scaler * _v.z,
		};
	}

}