#include "../../include/2D/Rect.hpp"
// #include "../../include/Camera/Camera2D.hpp"
// #include <include/EngineCore/EngineCore.hpp>
// #include <include/CommandList/CommandList.hpp>
// #include <include/PipelineState/RenderingPipeline2D.hpp>

/*namespace engine {

	Rect::Rect() 
		: transform()
		, vertexes()
		, indexData()
		, mesh()
		, worldMatrixBuffer()
		, worldMatrixBufferUploader()
	{
		vertexes.resize(4);
		vertexes[0] = { { -0.5, -0.5, 0.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } };
		vertexes[1] = { { -0.5,  0.5, 0.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } };
		vertexes[2] = { {  0.5,  0.5, 0.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } };
		vertexes[3] = { {  0.5, -0.5, 0.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } };

		indexData.setTriangle(0, 1, 2);
		indexData.setTriangle(0, 2, 3);

		if (!mesh.init(vertexes.data(), sizeof(Vertex2DColor), vertexes.size(), indexData)) {
			return;
		}

		worldMatrixBuffer.world = transform.getWorldMatrix();
		worldMatrixBufferUploader.init(&worldMatrixBuffer, sizeof(WorldMatrixBuffer));
	}

	Rect::~Rect() {

	}

	void Rect::setPosition(const Vector2& _pos) {
		transform.position = { _pos.x, _pos.y, 1.0f };
	}

	void Rect::setPosition(float _x, float _y) {
		transform.position = { _x, _y, 1.0f };
	}

	void Rect::setScale(const Vector2& _pos) {
		transform.scale = { _pos.x, _pos.y, 1.0f };

	}
	void Rect::setScale(float _x, float _y) {
		transform.scale = { _x, _y, 1.0f };
	}

	void Rect::setRotation(float _angle) {
		transform.rotation = Quaternion::rotationAxis({ 0.0f, 0.0f, 1.0f }, _angle);
	}

	void Rect::setColor(const ColorF& _color)
	{
		for (size_t i{ 0 }; i < vertexes.size(); ++i) {
			vertexes[i].color = { _color.r, _color.g, _color.b, _color.a };
		}
	}

	void Rect::draw() {
		//EnginePipeline2D()->setPipeline(RenderState::Default);

		//EngineCamera2D()->update();

		worldMatrixBuffer.world = transform.getWorldMatrix();
		worldMatrixBufferUploader.setConstantBuffer(1, &worldMatrixBuffer);

		mesh.setVertexBuffer(vertexes.data(), sizeof(Vertex2DColor), vertexes.size());

		mesh.draw();
	}
}
*/