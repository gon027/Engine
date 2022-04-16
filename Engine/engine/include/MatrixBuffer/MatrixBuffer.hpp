#pragma once

#include "../../../../../MathLib/MathLib/Math/include/Math.hpp"
#pragma comment(lib, "C:/Users/USER/source/repos/MathLib/x64/Debug/MathLib.lib")
using namespace gnLib;

namespace engine {

	struct WorldMatrixBuffer {
		Matrix4x4 world;  // 4 x 4 x 4 = 64
	};

	struct MatrixBuffer {
		Matrix4x4 view;
		Matrix4x4 projection;
	};

}