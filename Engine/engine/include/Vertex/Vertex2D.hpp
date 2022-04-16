#pragma once

#include <DirectXMath.h>

namespace engine {

	// 2D
	struct Vertex2D {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;
	};

	struct Vertex2D_Texture {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 uv;
		DirectX::XMFLOAT4 color;

		Vertex2D_Texture()
			: position({ 0.0f, 0.0f, 0.0f })
			, uv({ 0.0f, 0.0f })
			, color({ 1.0f, 1.0f, 1.0f, 1.0f })
		{}

		Vertex2D_Texture(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT2& _uv)
			: position(position)
			, uv(_uv)
			, color({ 1.0f, 1.0f, 1.0f, 1.0f })
		{}
	};

}