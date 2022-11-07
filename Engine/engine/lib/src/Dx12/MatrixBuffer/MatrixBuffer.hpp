#pragma once

#include "../Math/MathLib.hpp"

namespace engine {

	struct WorldMatrixBuffer {
		Matrix4x4 world;  // 4 x 4 x 4 = 64
	};

	struct MatrixBuffer {
		Matrix4x4 view;
		Matrix4x4 projection;
	};

}