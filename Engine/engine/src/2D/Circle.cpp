#include "..\..\include\2D\Circle.hpp"
// #include "../../include/Camera/Camera2D.hpp"
// #include <include/EngineCore/EngineCore.hpp>
// #include <include/CommandList/CommandList.hpp>
// #include <include/PipelineState/RenderingPipeline2D.hpp>

/*
namespace engine {

	namespace {
		static constexpr int VertexNum = 50;
		static constexpr float Radius = 70.0f;
		static constexpr float Tau = gnLib::pi * 2;
		float theta = Tau / static_cast<float>(VertexNum);
	}

	Circle::Circle()
		: transform()
		, vertexes()
		, indexData()
		, mesh()
		, worldMatrixBuffer()
		, worldMatrixBufferUploader()
	{
		vertexes.resize(VertexNum);
		for (int i = 0; i < VertexNum; ++i) {
			float x{ Radius * cosf(static_cast<float>(theta * i)) };
			float y{ Radius * sinf(static_cast<float>(theta * i)) };
			vertexes[i] = { { x, y, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
		}

		for (int i = 1; i < VertexNum - 1; ++i) {
			indexData.setTriangle(0, i, i + 1);
		}

		if (!mesh.init(vertexes.data(), sizeof(Vertex2DColor), vertexes.size(), indexData)) {
			return;
		}

		worldMatrixBuffer.world = transform.getWorldMatrix();
		worldMatrixBufferUploader.init(&worldMatrixBuffer, sizeof(WorldMatrixBuffer));
	}

	Circle::~Circle()
	{
	}

	void Circle::setPosition(const Vector2& _pos)
	{
		transform.position = { _pos.x, _pos.y, 1.0f };
	}

	void Circle::setPosition(float _x, float _y)
	{
		transform.position = { _x, _y, 1.0f };
	}

	void Circle::setScale(const Vector2& _scale)
	{
		transform.scale = { _scale.x, _scale.y, 1.0f };
	}

	void Circle::setScale(float _x, float _y)
	{
		transform.scale = { _x, _y, 1.0f };
	}

	void Circle::setRotation(float _angle)
	{
		transform.rotation = Quaternion::rotationAxis({ 0.0f, 0.0f, 1.0f }, _angle);
	}

	void Circle::draw()
	{
		//EnginePipeline2D()->setPipeline(RenderState::Default);

		//EngineCamera2D()->update();

		worldMatrixBuffer.world = transform.getWorldMatrix();
		worldMatrixBufferUploader.setConstantBuffer(1, &worldMatrixBuffer);

		mesh.draw();
	}
}
*/