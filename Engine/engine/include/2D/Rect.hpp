#pragma once

#include "../Type/Type.hpp"

// #include <include/MatrixBuffer/MatrixBuffer.hpp>
// #include <include/Buffer/ConstantBuffer.hpp>

#include "../../lib/Math/MathLib.hpp"
#include "../Transform/Transform.hpp"
#include "../IndexData/IndexData.hpp"

#include "../Mesh/Mesh.hpp"

#include "../Vertex/Vertex2D.hpp"

#include "../Color/Color.hpp"

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

		void setColor(const ColorF& _color);

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