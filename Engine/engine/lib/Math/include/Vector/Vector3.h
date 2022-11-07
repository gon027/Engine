#ifndef VECTOR3_H
#define VECTOR3_H

#include <string>

namespace gnLib {
	class Vector2;

	// 3次元ベクトルクラス
	class Vector3 {
	public :
		static Vector3 Up;
		static Vector3 Down;
		static Vector3 Left;
		static Vector3 Right;
		static Vector3 Back;
		static Vector3 Forward;
		static Vector3 One;
		static Vector3 Zero;

	public:
		float x;
		float y;
		float z;

		Vector3();
		Vector3(const Vector2& _v);
		Vector3(const Vector3& _v);
		Vector3(float _x, float _y, float z = 0.0f);
		Vector3(float _xyz);
		~Vector3() = default;

		void set(float _x, float _y, float _z);
		void set(const Vector3& _v);

		const float length() const;

		const float sqrtLength() const;

		const Vector3 normalized() const;

		// 半分の長さ
		const Vector3 half() const;

		// 内積
		const float dot(const Vector3& _v) const;

		// 外積
		const Vector3 cross(const Vector3& _v) const;

		// Vector2に変換
		const Vector2 toVector2();

		const Vector3 operator+() const;

		const Vector3 operator-() const;

		const Vector3 operator+(const Vector3& _v) const;

		const Vector3 operator-(const Vector3& _v) const;

		const Vector3 operator*(const Vector3& _v) const;

		const Vector3 operator/(const Vector3& _v) const;

		const Vector3& operator+=(const Vector3& _v);

		const Vector3& operator-=(const Vector3& _v);

		const Vector3& operator*=(const Vector3& _v);

		const Vector3& operator/=(const Vector3& _v);

		const bool operator==(const Vector3& _v) const;

		const bool operator!=(const Vector3& _v) const;

		const std::string toString() const;
	};

	const Vector3 operator*(float _scaler, const Vector3 _v);
}

#endif // !VECTOR3_H
