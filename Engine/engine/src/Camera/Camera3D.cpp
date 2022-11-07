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

}