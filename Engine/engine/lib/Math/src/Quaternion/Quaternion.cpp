#include "../../include/Quaternion/Quaternion.h"
#include "../../include/Matrix/Matrix4x4.h"
#include "../../include/Vector/Vector3.h"
#include <cmath>

#define tostr(value) std::to_string(value)

namespace gnLib {

    namespace {

        constexpr float EPS = 0.0001f;

        void SinCos(float& _sin, float& _cos, float _angle) {
            _sin = std::sinf(_angle);
            _cos = std::cosf(_angle);
        }

    }

    Quaternion gnLib::Quaternion::identity()
    {
        return { 0.0f, 0.0f, 0.0f, 1.0f };
    }

    Quaternion Quaternion::rotationAxis(const Vector3& _axis, float _angle)
    {
        float s, c;
        SinCos(s, c, _angle * 0.5f);

        const float x = _axis.x * s;
        const float y = _axis.y * s;
        const float z = _axis.z * s;
        const float w = c;

        return { x, y, z, w };
    }

    Quaternion Quaternion::rotationMatrix(const Matrix4x4& _m)
    {
        return Quaternion::identity();
    }

    Quaternion Quaternion::rotationRollPitchYaw(float _pitch, float _yaw, float _roll)
    {
        return Quaternion::identity();
    }

    Quaternion Quaternion::rotationRollPitchYaw(const Vector3& _angles)
    {
        return Quaternion::identity();
    }

    Quaternion::Quaternion(float _x, float _y, float _z, float _w)
        : x(_x)
        , y(_y)
        , z(_z)
        , w(_w)
    {
    }

    const float Quaternion::length()
    {
        return std::sqrtf(sqrtLength());
    }

    const float Quaternion::sqrtLength()
    {
        return x * x + y * y + z * z + w * w;
    }

    Quaternion Quaternion::normalized()
    {
        const auto len = length();

        // ’l‚ª0‚ÌŽž
        if (len < EPS) {
            return Quaternion::identity();
        }

        const auto mg = 1.0f / len;
        return {
            x * mg, y * mg, z * mg, w * mg
        };
    }

    Quaternion Quaternion::conjugate()
    {
        return { -x, -y, -z, w };
    }

    Quaternion Quaternion::inverse()
    {
        const auto len = sqrtLength();

        // 0ˆ—
        if (len < EPS) {
            return Quaternion::identity();
        }

        const auto oneOverLen = 1.0f / len;
        return {
            -x * oneOverLen,
            -y * oneOverLen,
            -z * oneOverLen,
            w * oneOverLen,
        };
    }

    Matrix4x4 Quaternion::toMatrix()
    {
        return {
            1.0f - 2.0f * y * y - 2.0f * z * z,
            2.0f * x * y + 2.0f * w * z,
            2.0f * x * z - 2.0f * w * y,
            0,
            2.0f * x * y - 2.0f * w * z,
            1.0f - 2.0f * x * x - 2.0f * z * z,
            2.0f * y * z + 2.0f * w * x,
            0,
            2.0f * x * z + 2.0f * w * y,
            2.0f * y * z - 2.0f * w * x,
            1.0f - 2.0f * x * x - 2.0f * y * y,
            0,
            0,
            0,
            0,
            1,
        };
    }

    const float Quaternion::dot(const Quaternion& _q)
    {
        return w * _q.w + x * _q.x + y * _q.y + z * _q.z;
    }

    const Quaternion Quaternion::operator*(const Quaternion& _q) const
    {
        const float rw{ w * _q.w - x * _q.x - y * _q.y - z * _q.z };
        const float rx{ w * _q.x + _q.w * x + y * _q.z - z * _q.y };
        const float ry{ w * _q.y + _q.w * y + z * _q.x - x * _q.z };
        const float rz{ w * _q.z + _q.w * z + x * _q.y - y * _q.x };

        return { rx, ry, rz, rw };
    }

    const Quaternion Quaternion::operator*=(const Quaternion& _q)
    {
        *this = *this * _q;
        return *this;
    }

    const bool Quaternion::operator==(const Quaternion& _q) const
    {
        return {
            x == _q.x && y == _q.y && z == _q.z && w == _q.w
        };
    }

    const bool Quaternion::operator!=(const Quaternion& _q) const
    {
        return !(*this == _q);
    }

    const std::string Quaternion::toString()
    {
        return { 
            "[ x = " + tostr(x) +
            ", y = " + tostr(y) +
            ", z = " + tostr(z) +
            ", w = " + tostr(w) + " ]\n"
        };
    }

}
