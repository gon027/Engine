#include "../../include/Matrix/Matrix4x3.h"

#define tostr(value) std::to_string(value)

namespace gnLib {

	namespace {

		float determinant2x2(
			float _m00, float _m01, 
			float _m10, float _m11) 
		{
			return (_m00 * _m11) - (_m01 * _m10);
		}

	}

	Matrix4x3 Matrix4x3::identity()
	{
		return {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 0.0f,
		};
	}

	Matrix4x3::Matrix4x3()
		: m00(0.0f), m01(0.0f), m02(0.0f)
		, m10(0.0f), m11(0.0f), m12(0.0f)
		, m20(0.0f), m21(0.0f), m22(0.0f)
		, m30(0.0f), m31(0.0f), m32(0.0f)
	{
	}

	Matrix4x3::Matrix4x3(const Matrix4x3& _mat)
		: m00(_mat.m00), m01(_mat.m01), m02(_mat.m02)
		, m10(_mat.m10), m11(_mat.m11), m12(_mat.m12)
		, m20(_mat.m20), m21(_mat.m21), m22(_mat.m22)
		, m30(_mat.m30), m31(_mat.m31), m32(_mat.m32)
	{
	}

	Matrix4x3::Matrix4x3(
		float _m00, float _m01, float _m02, 
		float _m10, float _m11, float _m12, 
		float _m20, float _m21, float _m22, 
		float _m30, float _m31, float _m32
	)
		: m00(_m00), m01(_m01), m02(_m02)
		, m10(_m10), m11(_m11), m12(_m12)
		, m20(_m20), m21(_m21), m22(_m22)
		, m30(_m30), m31(_m31), m32(_m32)
	{
	}

	Matrix4x3::Matrix4x3(const float _mat[12])
		: m00(_mat[0]), m01(_mat[1]), m02(_mat[2])
		, m10(_mat[3]), m11(_mat[4]), m12(_mat[5])
		, m20(_mat[6]), m21(_mat[7]), m22(_mat[8])
		, m30(_mat[9]), m31(_mat[10]), m32(_mat[11])
	{
	}

	// 3x3‚Ìs—ñ®‚ğŒvZ‚·‚é
	float Matrix4x3::determinant()
	{
		const float n00{ m00 * determinant2x2(m11, m12, m21, m22) };
		const float n01{ m01 * determinant2x2(m10, m12, m20, m22) };
		const float n02{ m02 * determinant2x2(m10, m11, m20, m21) };

		return n00 - n01 + n02;
	}

	void Matrix4x3::inverse()
	{
		const float det = determinant();

		if (std::abs(det) < 0.00001f) {
			return;
		}

		const float inv = 1.0f / det;

		const float n00{ inv * determinant2x2(m11, m12, m21, m22) };
		const float n10{ -inv * determinant2x2(m10, m12, m20, m22) };
		const float n20{ inv * determinant2x2(m10, m11, m20, m21) };
		
		const float n01{ -inv * determinant2x2(m01, m02, m21, m22) };
		const float n11{ inv * determinant2x2(m00, m02, m20, m22) };
		const float n21{ -inv * determinant2x2(m00, m01, m20, m21) };

		const float n02{ inv * determinant2x2(m01, m02, m11, m12) };
		const float n12{ -inv * determinant2x2(m00, m02, m10, m12) };
		const float n22{ inv * determinant2x2(m00, m01, m10, m11) };

		const float n30{ -(m30 * n00 + m31 * n10 + m32 * n20) };
		const float n31{ -(m30 * n01 + m31 * n11 + m32 * n21) };
		const float n32{ -(m30 * n02 + m31 * n12 + m32 * n22) };

		m00 = n00; m01 = n01; m02 = n02;
		m10 = n10; m11 = n11; m12 = n12;
		m20 = n20; m21 = n21; m22 = n22;
		m30 = n30; m31 = n31; m32 = n32;
	}

	// ˆê”Ô‰º‚Ì—ñ(m30, m31, m32)‚Í0.0f‚ğ‘ã“ü‚·‚é
	void Matrix4x3::transpose()
	{
		std::swap(m01, m10);
		std::swap(m02, m20);
		std::swap(m12, m21);
		m30 = 0.0f;
		m31 = 0.0f;
		m32 = 0.0f;
	}

	const Matrix4x3 Matrix4x3::operator+(const Matrix4x3& _mat) const
	{
		return {
			m00 + _mat.m00, m01 + _mat.m01, m02 + _mat.m02,
			m10 + _mat.m10, m11 + _mat.m11, m12 + _mat.m12,
			m20 + _mat.m20, m21 + _mat.m21, m22 + _mat.m22,
			m30 + _mat.m30, m31 + _mat.m31, m32 + _mat.m32,
		};
	}

	const Matrix4x3 Matrix4x3::operator-(const Matrix4x3& _mat) const
	{
		return {
			m00 - _mat.m00, m01 - _mat.m01, m02 - _mat.m02,
			m10 - _mat.m10, m11 - _mat.m11, m12 - _mat.m12,
			m20 - _mat.m20, m21 - _mat.m21, m22 - _mat.m22,
			m30 - _mat.m30, m31 - _mat.m31, m32 - _mat.m32,
		};
	}

	const Matrix4x3 Matrix4x3::operator*(const Matrix4x3& _mat) const
	{
		const float nm00{ m00 * _mat.m00 + m01 * _mat.m10 + m02 * _mat.m20 };
		const float nm01{ m00 * _mat.m01 + m01 * _mat.m11 + m02 * _mat.m21 };
		const float nm02{ m00 * _mat.m02 + m01 * _mat.m12 + m02 * _mat.m22 };

		const float nm10{ m10 * _mat.m00 + m11 * _mat.m10 + m12 * _mat.m20 };
		const float nm11{ m10 * _mat.m01 + m11 * _mat.m11 + m12 * _mat.m21 };
		const float nm12{ m10 * _mat.m02 + m11 * _mat.m12 + m12 * _mat.m22 };

		const float nm20{ m20 * _mat.m00 + m21 * _mat.m10 + m22 * _mat.m20 };
		const float nm21{ m20 * _mat.m01 + m21 * _mat.m11 + m22 * _mat.m21 };
		const float nm22{ m20 * _mat.m02 + m21 * _mat.m12 + m22 * _mat.m22 };

		const float nm30{ m30 * _mat.m00 + m31 * _mat.m10 + m32 * _mat.m20 + _mat.m30 };
		const float nm31{ m30 * _mat.m01 + m31 * _mat.m11 + m32 * _mat.m21 + _mat.m31 };
		const float nm32{ m30 * _mat.m02 + m31 * _mat.m12 + m32 * _mat.m22 + _mat.m32 };

		return {
			nm00, nm01, nm02,
			nm10, nm11, nm12,
			nm20, nm21, nm22,
			nm30, nm31, nm32,
		};
	}

	const Matrix4x3 Matrix4x3::operator*(float _scalar) const
	{
		return {
			m00 * _scalar, m01 * _scalar, m02 * _scalar,
			m10 * _scalar, m11 * _scalar, m12 * _scalar,
			m20 * _scalar, m21 * _scalar, m22 * _scalar,
			m30 * _scalar, m31 * _scalar, m32 * _scalar,
		};
	}

	const Matrix4x3 operator*(float _scalar, const Matrix4x3& _mat)
	{
		return {
		   _scalar * _mat.m00, _scalar * _mat.m01, _scalar * _mat.m02,
		   _scalar * _mat.m10, _scalar * _mat.m11, _scalar * _mat.m12,
		   _scalar * _mat.m20, _scalar * _mat.m21, _scalar * _mat.m22,
		   _scalar * _mat.m30, _scalar * _mat.m31, _scalar * _mat.m32,
		};
	}

	const Matrix4x3& Matrix4x3::operator+=(const Matrix4x3& _mat)
	{
		*this = *this + _mat;
		return *this;
	}

	const Matrix4x3& Matrix4x3::operator-=(const Matrix4x3& _mat)
	{
		*this = *this - _mat;
		return *this;
	}

	const Matrix4x3& Matrix4x3::operator*=(const Matrix4x3& _mat)
	{
		*this = *this * _mat;
		return *this;
	}

	const bool Matrix4x3::operator==(const Matrix4x3& _rm) const
	{
		return {
		   m00 == _rm.m00 && m01 == _rm.m01 && m02 == _rm.m02 &&
		   m10 == _rm.m10 && m11 == _rm.m11 && m12 == _rm.m12 &&
		   m20 == _rm.m20 && m21 == _rm.m21 && m22 == _rm.m22 &&
		   m30 == _rm.m30 && m31 == _rm.m31 && m32 == _rm.m32 
		};
	}

	const bool Matrix4x3::operator!=(const Matrix4x3& _rm) const
	{
		return !(*this == _rm);
	}

	const std::string Matrix4x3::toString()
	{
		return {
			"[ m00 = " + tostr(m00) + ", m01 = " + tostr(m01) + ", m02 = " + tostr(m02) + " ]\n"
			"[ m10 = " + tostr(m10) + ", m11 = " + tostr(m11) + ", m12 = " + tostr(m12) + " ]\n"
			"[ m20 = " + tostr(m20) + ", m21 = " + tostr(m21) + ", m22 = " + tostr(m22) + " ]\n"
			"[ m30 = " + tostr(m30) + ", m31 = " + tostr(m31) + ", m32 = " + tostr(m32) + " ]\n"
		};
	}

}