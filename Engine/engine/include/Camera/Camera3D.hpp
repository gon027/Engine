#pragma once

#include "../../lib/Math/MathLib.hpp"

namespace engine {

	class Camera3D {
	public:
		Camera3D();
		~Camera3D() = default;

		void setPos(const Vector3& _pos);

		void translate(float _x, float _y, float _z);

		void rotateX(float _angle);
		void rotateY(float _angle);
		void rotateZ(float _angle);

		void rotate(const Vector3& _axis);

		Matrix4x4& getView() {
			view = Matrix4x4::lookAtLH(eye, target, up);
			return view;
		}

		Matrix4x4& getProjection() {
			return projection;
		}

		Matrix4x4 getViewProjection() {
			return view * projection;
		}

	private:
		struct Perspective {
			float fovAngleY;
			float aspect;
			float nearZ;
			float farZ;
		};

		Vector3 eye;
		Vector3 target;
		Vector3 up;

		Perspective perspective;

		Matrix4x4 view;
		Matrix4x4 projection;
	};

}