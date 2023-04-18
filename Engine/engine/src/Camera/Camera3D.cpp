#include "../../../engine/include/Camera/Camera3D.hpp"

namespace engine {

	namespace {

		float toRadian(float _d) {
			return _d * 3.14159246f / 180.0f;
		}
	}

	Camera3D::Camera3D()
		: eye({ 0, 0, -5 })
		, target({ 0, 0, 0 })
		, up({ 0, 1, 0 })
		, perspective({ toRadian(45.0f), (640.0f / 480.0f), 1.0f, 100.0f })
		, view({ Matrix4x4::identity() })
		, projection({ Matrix4x4::identity() })
	{
		view = Matrix4x4::lookAtLH(
			eye, target, up
		);

		projection = Matrix4x4::perspectiveFovLH(
			perspective.fovAngleY,
			perspective.aspect,
			perspective.nearZ,
			perspective.farZ
		);
	}

	void Camera3D::setPos(const Vector3& _pos)
	{
		eye = _pos;
		target = _pos;
		target.z -= 1.0f;
	}

	void Camera3D::translate(float _x, float _y, float _z)
	{
		eye += { _x, _y, _z };
		target += { _x, _y, _z };
	}

}