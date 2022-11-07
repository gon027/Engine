#include "../../include/Camera/Camera2D.hpp"

namespace engine {
	Camera2D::Camera2D()
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
		//, matrixBuffer()
		//, matrixBufferUploader()
	{
		view = Matrix4x4::lookAtLH(eye, target, up);
		projection = Matrix4x4::orthographicLH(viewWidth, viewHeight, nearZ, farZ);
	}

	void Camera2D::setPosition(float _x, float _y) {
		position.set(_x, _y, 0.0f);

		eye += position;
		target += position;
	}

	bool Camera2D::init()
	{
		/*
		matrixBuffer.view = view;
		matrixBuffer.projection = projection;
		matrixBufferUploader.init(&matrixBuffer, sizeof(matrixBuffer));
		*/
		return true;
	}

	void Camera2D::update()
	{
		/*
		matrixBuffer.view = view;
		matrixBuffer.projection = projection;
		matrixBufferUploader.setConstantBuffer(0, &matrixBuffer);
		*/
	}
}
