#pragma once

#include "../../lib/Math/MathLib.hpp"

#include "../Type/Type.hpp"

// #include <include/MatrixBuffer/MatrixBuffer.hpp>
// #include <include/Buffer/ConstantBuffer.hpp>

#include "../Transform/Transform.hpp"
#include "../IndexData/IndexData.hpp"

#include "../Mesh/Mesh.hpp"

#include "../Vertex/Vertex2D.hpp"

namespace engine {

	class Circle {
	public:
		Circle();
		~Circle();

		void setPosition(const Vector2& _pos);
		void setPosition(float _x, float _y);

		void setScale(const Vector2& _scale);
		void setScale(float _x, float _y);

		void setRotation(float _angle);

		void draw();

	private:
		Transform transform;

		std::vector<Vertex2DColor> vertexes;
		IndexData indexData;

		Mesh mesh;

		// WorldMatrixBuffer worldMatrixBuffer;
		// ConstantBuffer    worldMatrixBufferUploader;
	};

}