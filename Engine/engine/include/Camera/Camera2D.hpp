#pragma once

#include "../../../../../MathLib/MathLib/Math/include/Math.hpp"
#pragma comment(lib, "C:/Users/USER/source/repos/MathLib/x64/Debug/MathLib.lib")
using namespace gnLib;

namespace engine {

	class Camera2D {
	public:
		Camera2D()
			: eye({ 0.0f, 0.0f, -1.0f })
			, target({ 0.0f, 0.0f, 0.0f })
			, up({ 0.0f, 1.0f, 0.0f })
			, nearZ(1.0f)
			, farZ(100.0f)
			, viewWidth(640.0f)
			, viewHeight(480.0f)
			, view()
			, projection()
			, position(Vector3::Zero)
		{
			view = Matrix4x4::lookAtLH(eye, target, up);
			projection = Matrix4x4::orthographicLH(viewWidth, viewHeight, nearZ, farZ);
		}
		~Camera2D() = default;

		void setPosition(float _x, float _y) {
			position.set(_x, _y, 0.0f);

			eye += position;
			target += position;
		}

		Matrix4x4& getView() {
			view = Matrix4x4::lookAtLH(eye, target, up);
			return view;
		}

		Matrix4x4& getProjection() {
			return projection;
		}

	private:
		float nearZ;
		float farZ;

		float viewWidth;
		float viewHeight;

		Vector3 eye;
		Vector3 target;
		Vector3 up;

		Matrix4x4 view;
		Matrix4x4 projection;

		Vector3 position;
	};

}