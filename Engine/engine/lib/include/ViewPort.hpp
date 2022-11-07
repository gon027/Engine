#pragma once

namespace engine {

	struct ViewPort {
		float topLeftX = 0.0f;
		float topLeftY = 0.0f;
		float width = 0.0f;
		float height = 0.0f;
		float minDepth = 0.0f;
		float maxDepth = 1.0f;
	};

}