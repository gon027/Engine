#pragma once

#include "../../../../../MathLib/MathLib/Math/include/Math.hpp"
#pragma comment(lib, "C:/Users/USER/source/repos/MathLib/x64/Debug/MathLib.lib")
using namespace gnLib;

namespace engine {

	struct Transform {
		Transform()
			: position(Vector3::Zero)
			, rotation(Quaternion::identity())
			, scale({ 1.0f, 1.0f, 1.0f })
		{};
		~Transform() = default;

		Matrix4x4 getWorldMatrix() {
			auto t = Matrix4x4::translation(position);
			auto r = rotation.toMatrix();
			auto s = Matrix4x4::scaling(scale);
			return s * r * t;
		}

		Vector3 position;
		Quaternion rotation;
		Vector3 scale;
	};

}