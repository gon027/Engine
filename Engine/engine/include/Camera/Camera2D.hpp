#pragma once

#include "../../lib/Math/MathLib.hpp"

// #include <include/MatrixBuffer/MatrixBuffer.hpp>
// #include <include/Buffer/ConstantBuffer.hpp>

namespace engine {

	class Camera2D {
	public:
		Camera2D();
		~Camera2D() = default;

		bool init();

		void update();

		void setPosition(float _x, float _y);

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

		// MatrixBuffer matrixBuffer;
		// ConstantBuffer matrixBufferUploader;
	};

}