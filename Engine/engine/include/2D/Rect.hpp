#pragma once

#include "../../lib/Math/MathLib.hpp"

#include <include/Type/Type.hpp>

#include <include/MatrixBuffer/MatrixBuffer.hpp>
#include <include/Buffer/ConstantBuffer.hpp>

#include "../Transform/Transform.hpp"
#include "../IndexData/IndexData.hpp"

#include "../Mesh/Mesh.hpp"

namespace engine {

	class Rect {
	public:
		Rect();
		~Rect();

		void setPosition(const Vector2& _pos);
		void setPosition(float _x, float _y);

		void setScale(const Vector2& _pos);
		void setScale(float _x, float _y);

		void setRotation(float _angle);

		void draw();

	private:
		Transform transform;

		// Todo: Œã‚ÅˆÚ“®‚³‚¹‚é
		struct Vertex {
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT4 color;
		};

		std::vector<Vertex> vertexes;
		IndexData indexData;

		Mesh mesh;

		WorldMatrixBuffer worldMatrixBuffer;
		ConstantBuffer    worldMatrixBufferUploader;
	};

}