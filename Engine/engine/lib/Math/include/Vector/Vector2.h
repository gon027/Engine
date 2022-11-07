#ifndef VECTOR2_H
#define VECTOR2_H

#include <string>

namespace gnLib {
	class Vector3;

	// 2次元ベクトルクラス
	class Vector2 {
	public:
		static Vector2 Up;
		static Vector2 Down;
		static Vector2 Left;
		static Vector2 Right;
		static Vector2 One;
		static Vector2 Zero;

	public:
		float x;
		float y;

		Vector2();
		Vector2(const Vector2& _v);
		Vector2(float _x, float _y);
		Vector2(float _xy);
		~Vector2() = default;

		void set(float _x, float _y);
		void set(const Vector2& _v);

		const float length() const;

		const float sqrtLength() const;

		const Vector2 normalized() const;

		// ベクトルの半分の値
		const Vector2 half() const;

		// 内積
		const float dot(const Vector2& _v);

		// 外積
		const float cross(const Vector2& _v);

		// Vector3に変換
		Vector3 toVector3();

		const Vector2 operator+() const;

		const Vector2 operator-() const;

		const Vector2 operator+(const Vector2& _v) const;

		const Vector2 operator-(const Vector2& _v) const;

		const Vector2 operator*(const Vector2& _v) const;

		const Vector2 operator/(const Vector2& _v) const;

		const Vector2& operator+=(const Vector2& _v);

		const Vector2& operator-=(const Vector2& _v);

		const Vector2& operator*=(const Vector2& _v);

		const Vector2& operator/=(const Vector2& _v);

		const bool operator==(const Vector2& _v) const;

		const bool operator!=(const Vector2& _v) const;

		const std::string toString() const;
	};

	const Vector2 operator*(float _scaler, const Vector2& _v);
}


#endif // !VECTOR2_H
