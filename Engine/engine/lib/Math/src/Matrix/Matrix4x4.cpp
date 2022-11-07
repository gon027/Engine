#include "../../include/Matrix/Matrix4x4.h"
#include "../../include/Vector/Vector3.h"
#include <string>
#include <cmath>

#define tostr(value) std::to_string(value)

namespace gnLib {

    namespace {

        // 3x3çsóÒÇÃçsóÒéÆ
        const float determinant3x3(
            float _m00, float _m01, float _m02,
            float _m10, float _m11, float _m12,
            float _m20, float _m21, float _m22) 
        {
            // ëŒäp
            const float a0{ _m00 * _m11 * _m22 };
            const float a1{ _m01 * _m12 * _m20 };
            const float a2{ _m02 * _m10 * _m21 };

            // îÒëŒäp
            const float b0{ _m02 * _m11 * _m20 };
            const float b1{ _m01 * _m10 * _m22 };
            const float b2{ _m00 * _m12 * _m21 };

            return a0 + a1 + a2 - b0 - b1 - b2;
        }
    }

    Matrix4x4 Matrix4x4::identity()
    {
        return Matrix4x4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    Matrix4x4 Matrix4x4::rotationX(float _angle)
    {
        const float s{ std::sinf(_angle) };
        const float c{ std::cosf(_angle) };

        return {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, c, s, 0.0f,
            0.0f, -s, c, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    Matrix4x4 Matrix4x4::rotationY(float _angle)
    {
        const float s{ std::sinf(_angle) };
        const float c{ std::cosf(_angle) };

        return {
            c, 0.0f, -s, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            s, 0.0f, c, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    Matrix4x4 Matrix4x4::rotationZ(float _angle)
    {
        const float s{ std::sinf(_angle) };
        const float c{ std::cosf(_angle) };

        return {
            c, s, 0.0f, 0.0f,
            -s, c, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    Matrix4x4 Matrix4x4::rotationRollPitchYaw(float _pitch, float _yaw, float _roll)
    {
        return rotationZ(_roll) * rotationX(_pitch) * rotationY(_yaw);
    }

    Matrix4x4 Matrix4x4::rotationRollPitchYaw(const Vector3& _angles)
    {
        return rotationZ(_angles.z) * rotationX(_angles.x) * rotationY(_angles.y);
    }

    Matrix4x4 Matrix4x4::scaling(float _scallX, float _scallY, float _scallZ)
    {
        return {
            _scallX, 0.0f, 0.0f, 0.0f,
            0.0f, _scallY, 0.0f, 0.0f,
            0.0f, 0.0f, _scallZ, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f,
        };
    }

    Matrix4x4 Matrix4x4::scaling(const Vector3& _scall)
    {
        return {
            _scall.x, 0.0f, 0.0f, 0.0f,
            0.0f, _scall.y, 0.0f, 0.0f,
            0.0f, 0.0f, _scall.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f,
        };
    }

    Matrix4x4 Matrix4x4::translation(float _offsetX, float _offsetY, float _offsetZ)
    {
        return {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            _offsetX, _offsetY, _offsetZ, 1.0f
        };
    }

    Matrix4x4 Matrix4x4::translation(const Vector3& _offset)
    {
        return {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            _offset.x, _offset.y, _offset.z, 1.0f
        };
    }

    Matrix4x4 Matrix4x4::lookAtLH(const Vector3& _eye, const Vector3& _focus, const Vector3& _up)
    {
        const auto zAxis{ (_focus - _eye).normalized() };
        const auto xAxis{ _up.cross(zAxis).normalized() };
        const auto yAxis{ zAxis.cross(xAxis) };
        
        return {
            xAxis.x, yAxis.x, zAxis.x, 0.0f,
            xAxis.y, yAxis.y, zAxis.y, 0.0f,
            xAxis.z, yAxis.z, zAxis.z, 0.0f,
            -xAxis.dot(_eye),  -yAxis.dot(_eye), -zAxis.dot(_eye), 1.0f
        };
    }

    Matrix4x4 Matrix4x4::orthographicLH(float _viewWidth, float _viewHeight, float _nearZ, float _farZ)
    {
        const auto zDiff = _farZ - _nearZ;

        return {
            2.0f / _viewWidth, 0.0f, 0.0f, 0.0f,
            0.0f, 2.0f / _viewHeight, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f / zDiff, 0.0f,
            0.0f, 0.0f, -_nearZ / zDiff, 1.0f,
        };
    }

    Matrix4x4 Matrix4x4::perspectiveFovLH(float _fovAngleY, float _aspectRatio, float _nearZ, float _farZ)
    {
        const auto h = 1.0f / std::tanf(_fovAngleY * 0.5f);
        const auto w = h / _aspectRatio;
        const auto zDiff = _farZ - _nearZ;

        return {
            w, 0.0f, 0.0f, 0.0f,
            0.0f, h, 0.0f, 0.0f,
            0.0f, 0.0f, _farZ / zDiff, 1.0f,
            0.0f, 0.0f, -(_farZ * _nearZ) / zDiff, 0.0f,
        };
    }

    Matrix4x4 Matrix4x4::perspectiveLH(float _viewWidth, float _viewHeight, float _nearZ, float _farZ)
    {
        const auto zDiff{ _farZ - _nearZ };

        return {
            2.0f * _nearZ / _viewWidth, 0.0f, 0.0f, 0.0f,
            0.0f, 2.0f * _nearZ / _viewHeight, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f / zDiff, 1.0f,
            0.0f, 0.0f, -_nearZ / zDiff, 0.0f,
        };
    }


    Matrix4x4::Matrix4x4()
        : m00(0.0f), m01(0.0f), m02(0.0f), m03(0.0f)
        , m10(0.0f), m11(0.0f), m12(0.0f), m13(0.0f)
        , m20(0.0f), m21(0.0f), m22(0.0f), m23(0.0f)
        , m30(0.0f), m31(0.0f), m32(0.0f), m33(0.0f)
    {
    }

    Matrix4x4::Matrix4x4(const Matrix4x4& _m)
        : m00(_m.m00), m01(_m.m01), m02(_m.m02), m03(_m.m03)
        , m10(_m.m10), m11(_m.m11), m12(_m.m12), m13(_m.m13)
        , m20(_m.m20), m21(_m.m21), m22(_m.m22), m23(_m.m23)
        , m30(_m.m30), m31(_m.m31), m32(_m.m32), m33(_m.m33)
    {
    }

    Matrix4x4::Matrix4x4(
        float _m00, float _m01, float _m02, float _m03,
        float _m10, float _m11, float _m12, float _m13,
        float _m20, float _m21, float _m22, float _m23,
        float _m30, float _m31, float _m32, float _m33
    )
        : m00(_m00), m01(_m01), m02(_m02), m03(_m03)
        , m10(_m10), m11(_m11), m12(_m12), m13(_m13)
        , m20(_m20), m21(_m21), m22(_m22), m23(_m23)
        , m30(_m30), m31(_m31), m32(_m32), m33(_m33)
    {
    }

    Matrix4x4::Matrix4x4(const float _m[16])
        : m00(_m[0]), m01(_m[1]), m02(_m[2]), m03(_m[3])
        , m10(_m[4]), m11(_m[5]), m12(_m[6]), m13(_m[7])
        , m20(_m[8]), m21(_m[9]), m22(_m[10]), m23(_m[11])
        , m30(_m[12]), m31(_m[13]), m32(_m[14]), m33(_m[15])
    {
    }
    
    float Matrix4x4::determinant()
    {
        const float a0{ m00 * determinant3x3(m11, m12, m13, m21, m22, m23, m31, m32, m33) };
        const float a1{ m10 * determinant3x3(m01, m02, m03, m21, m22, m23, m31, m32, m33) };
        const float a2{ m20 * determinant3x3(m01, m02, m03, m11, m12, m13, m31, m32, m33) };
        const float a3{ m30 * determinant3x3(m01, m02, m03, m11, m12, m13, m21, m22, m23) };

        return a0 - a1 + a2 - a3;
    }

    void Matrix4x4::inverse()
    {
        const float det = determinant();

        // çsóÒéÆÇ™0ÇÃéûÅAãtçsóÒÇ≈ÇÕÇ»Ç≠å≥ÇÃçsóÒÇï‘Ç∑
        if (std::abs(det) < 0.00001f) {
            return;
        }

        const float inv = 1.0f / det;

        // äeó]âCéqÇåvéZ
        const float n00{ inv * determinant3x3(m11, m12, m13, m21, m22, m23, m31, m32, m33) };
        const float n10{ -inv * determinant3x3(m10, m12, m13, m20, m22, m23, m30, m32, m33) };
        const float n20{ inv * determinant3x3(m10, m11, m13, m20, m21, m23, m30, m31, m33) };
        const float n30{ -inv * determinant3x3(m10, m11, m12, m20, m21, m22, m30, m31, m32) };

        const float n01{ -inv * determinant3x3(m01, m02, m03, m21, m22, m23, m31, m32, m33) };
        const float n11{ inv * determinant3x3(m00, m02, m03, m20, m22, m23, m30, m32, m33) };
        const float n21{ -inv * determinant3x3(m00, m01, m03, m20, m21, m23, m30, m31, m33) };
        const float n31{ inv * determinant3x3(m00, m01, m02, m20, m21, m22, m30, m31, m32) };

        const float n02{ inv * determinant3x3(m01, m02, m03, m11, m12, m13, m31, m32, m33) };
        const float n12{ -inv * determinant3x3(m00, m02, m03, m10, m12, m13, m30, m32, m33) };
        const float n22{ inv * determinant3x3(m00, m01, m03, m10, m11, m13, m30, m31, m33) };
        const float n32{ -inv * determinant3x3(m00, m01, m02, m10, m11, m12, m30, m31, m32) };

        const float n03{ -inv * determinant3x3(m01, m02, m03, m11, m12, m13, m21, m22, m23) };
        const float n13{ inv * determinant3x3(m00, m02, m03, m10, m12, m13, m20, m22, m23) };
        const float n23{ -inv * determinant3x3(m00, m01, m03, m10, m11, m13, m20, m21, m23) };
        const float n33{ inv * determinant3x3(m00, m01, m02, m10, m11, m12, m20, m21, m22) };

        m00 = n00; m01 = n01; m02 = n02; m03 = n03;
        m10 = n10; m11 = n11; m12 = n12; m13 = n13;
        m20 = n20; m21 = n21; m22 = n22; m23 = n23;
        m30 = n30; m31 = n31; m32 = n32; m33 = n33;
    }

    void Matrix4x4::transpose()
    {
        std::swap(m01, m10);
        std::swap(m02, m20);
        std::swap(m03, m30);
        std::swap(m13, m31);
        std::swap(m12, m21);
        std::swap(m23, m32);
    }

    const Matrix4x4 Matrix4x4::operator+(const Matrix4x4& _m) const
    {
        return {
            m00 + _m.m00, m01 + _m.m01, m02 + _m.m02, m03 + _m.m03,
            m10 + _m.m10, m11 + _m.m11, m12 + _m.m12, m13 + _m.m13,
            m20 + _m.m20, m21 + _m.m21, m22 + _m.m22, m23 + _m.m23,
            m30 + _m.m30, m31 + _m.m31, m32 + _m.m32, m33 + _m.m33
        };
    }

    const Matrix4x4 Matrix4x4::operator-(const Matrix4x4& _m) const
    {
        return {
            m00 - _m.m00, m01 - _m.m01, m02 - _m.m02, m03 - _m.m03,
            m10 - _m.m10, m11 - _m.m11, m12 - _m.m12, m13 - _m.m13,
            m20 - _m.m20, m21 - _m.m21, m22 - _m.m22, m23 - _m.m23,
            m30 - _m.m30, m31 - _m.m31, m32 - _m.m32, m33 - _m.m33
        };
    }

    const Matrix4x4 Matrix4x4::operator*(const Matrix4x4& _m) const
    {
        const float nm00{ m00 * _m.m00 + m01 * _m.m10 + m02 * _m.m20 + m03 * _m.m30 };
        const float nm01{ m00 * _m.m01 + m01 * _m.m11 + m02 * _m.m21 + m03 * _m.m31 };
        const float nm02{ m00 * _m.m02 + m01 * _m.m12 + m02 * _m.m22 + m03 * _m.m32 };
        const float nm03{ m00 * _m.m03 + m01 * _m.m13 + m02 * _m.m23 + m03 * _m.m33 };

        const float nm10{ m10 * _m.m00 + m11 * _m.m10 + m12 * _m.m20 + m13 * _m.m30 };
        const float nm11{ m10 * _m.m01 + m11 * _m.m11 + m12 * _m.m21 + m13 * _m.m31 };
        const float nm12{ m10 * _m.m02 + m11 * _m.m12 + m12 * _m.m22 + m13 * _m.m32 };
        const float nm13{ m10 * _m.m03 + m11 * _m.m13 + m12 * _m.m23 + m13 * _m.m33 };

        const float nm20{ m20 * _m.m00 + m21 * _m.m10 + m22 * _m.m20 + m23 * _m.m30 };
        const float nm21{ m20 * _m.m01 + m21 * _m.m11 + m22 * _m.m21 + m23 * _m.m31 };
        const float nm22{ m20 * _m.m02 + m21 * _m.m12 + m22 * _m.m22 + m23 * _m.m32 };
        const float nm23{ m20 * _m.m03 + m21 * _m.m13 + m22 * _m.m23 + m23 * _m.m33 };

        const float nm30{ m30 * _m.m00 + m31 * _m.m10 + m32 * _m.m20 + m33 * _m.m30 };
        const float nm31{ m30 * _m.m01 + m31 * _m.m11 + m32 * _m.m21 + m33 * _m.m31 };
        const float nm32{ m30 * _m.m02 + m31 * _m.m12 + m32 * _m.m22 + m33 * _m.m32 };
        const float nm33{ m30 * _m.m03 + m31 * _m.m13 + m32 * _m.m23 + m33 * _m.m33 };

        return {
            nm00, nm01, nm02, nm03,
            nm10, nm11, nm12, nm13,
            nm20, nm21, nm22, nm23,
            nm30, nm31, nm32, nm33
        };
    }

    const Matrix4x4 Matrix4x4::operator*(float _scalar) const
    {
        return {
            m00 * _scalar, m01 * _scalar, m02 * _scalar, m03 * _scalar,
            m10 * _scalar, m11 * _scalar, m12 * _scalar, m13 * _scalar,
            m20 * _scalar, m21 * _scalar, m22 * _scalar, m23 * _scalar,
            m30 * _scalar, m31 * _scalar, m32 * _scalar, m33 * _scalar
        };
    }

    const Matrix4x4 operator*(float _scalar, const Matrix4x4& _m)
    {
        return {
           _scalar * _m.m00, _scalar * _m.m01, _scalar * _m.m02, _scalar * _m.m03,
           _scalar * _m.m10, _scalar * _m.m11, _scalar * _m.m12, _scalar * _m.m13,
           _scalar * _m.m20, _scalar * _m.m21, _scalar * _m.m22, _scalar * _m.m23,
           _scalar * _m.m30, _scalar * _m.m31, _scalar * _m.m32, _scalar * _m.m33
        };
    }

    const bool Matrix4x4::operator==(const Matrix4x4& _m) const
    {
        return {
            m00 == _m.m00 && m01 == _m.m01 && m02 == _m.m02 && m03 == _m.m03 &&
            m10 == _m.m10 && m11 == _m.m11 && m12 == _m.m12 && m13 == _m.m13 &&
            m20 == _m.m20 && m21 == _m.m21 && m22 == _m.m22 && m23 == _m.m23 &&
            m30 == _m.m30 && m31 == _m.m31 && m32 == _m.m32 && m33 == _m.m33
        };
    }

    const bool Matrix4x4::operator!=(const Matrix4x4& _m) const
    {
        return !(*this == _m);
    }

    const Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& _m)
    {
        *this = *this + _m;
        return *this;
    }

    const Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& _m)
    {
        *this = *this - _m;
        return *this;
    }

    const Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& _m)
    {
        *this = *this * _m;
        return *this;
    }

    const std::string Matrix4x4::toString()
    {
        return {
            "[ m00 = " + tostr(m00) + ", m01 = " + tostr(m01) + ", m02 = " + tostr(m02) + ", m03 =  " + tostr(m03) + " ]\n"
            "[ m10 = " + tostr(m10) + ", m11 = " + tostr(m11) + ", m12 = " + tostr(m12) + ", m13 =  " + tostr(m13) + " ]\n"
            "[ m20 = " + tostr(m20) + ", m21 = " + tostr(m21) + ", m22 = " + tostr(m22) + ", m23 =  " + tostr(m23) + " ]\n"
            "[ m30 = " + tostr(m30) + ", m31 = " + tostr(m31) + ", m32 = " + tostr(m32) + ", m33 =  " + tostr(m33) + " ]\n"
        };
    }

}