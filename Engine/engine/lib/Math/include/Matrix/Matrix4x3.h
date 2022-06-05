#ifndef MATRIX4X3_H
#define MATRIX4X3_H

#include <string>

namespace gnLib {

	struct Matrix4x3 {
	public:
		static Matrix4x3 identity();

	public:
		Matrix4x3();
		Matrix4x3(const Matrix4x3& _mat);
		Matrix4x3(
			float _m00, float _m01, float _m02,
			float _m10, float _m11, float _m12,
			float _m20, float _m21, float _m22,
			float _m30, float _m31, float _m32
		);
		Matrix4x3(const float _mat[12]);
		~Matrix4x3() = default;;

		// çsóÒéÆ
		float determinant();

		// ãtçsóÒ
		void inverse();

		// ì]íuçsóÒ
		void transpose();

		// operator
		const Matrix4x3 operator+(const Matrix4x3& _mat) const;

		const Matrix4x3 operator-(const Matrix4x3& _mat) const;

		const Matrix4x3 operator*(const Matrix4x3& _mat) const;
		const Matrix4x3 operator*(float _scalar) const;
		const friend Matrix4x3 operator*(float _scalar, const Matrix4x3& _mat);

		const Matrix4x3& operator+=(const Matrix4x3& _mat);

		const Matrix4x3& operator-=(const Matrix4x3& _mat);

		const Matrix4x3& operator*=(const Matrix4x3& _mat);

		const bool operator==(const Matrix4x3& _rm) const;

		const bool operator!=(const Matrix4x3& _rm) const;

		const std::string toString();

	public:
		union {
			float m[4][3];

			struct {
				float m00, m01, m02;
				float m10, m11, m12;
				float m20, m21, m22;
				float m30, m31, m32;
			};
		};
	};

}

#endif // !MATRIX4X3_H
