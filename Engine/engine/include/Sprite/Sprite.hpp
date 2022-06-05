#pragma once

#include <vector>
#include <memory>
#include "../Transform/Transform.hpp"

#include <include/Vertex/Vertex2D.hpp>
#include <include/Type/Type.hpp>
#include <include/Buffer/VertexBuffer.hpp>
#include <include/Buffer/IndexBuffer.hpp>

#include <include/MatrixBuffer/MatrixBuffer.hpp>
#include <include/Buffer/ConstantBuffer.hpp>

namespace engine {

	class Texture;
	using TexturePtr = std::shared_ptr<Texture>;

	enum class SpriteAlignment {
		Center,
		TopLeft,
		TopCenter,
		TopRight,
		LeftCenter,
		RightCenter,
		BottomLeft,
		BottomCenter,
		BottomRight
	};

	class Sprite {
	public:
		Sprite();
		Sprite(TexturePtr _texture);
		~Sprite() = default;

		bool init(TexturePtr& _texture);

		void setTexture(TexturePtr& _texture);

		void setAlignment(SpriteAlignment _spriteAlignment);

		void setTransform(const Transform& _transform);

		void setPosition(const gnLib::Vector3& _position);

		void setRotation(const gnLib::Quaternion& _rotation);

		void setScale(const gnLib::Vector3& _scale);

		u64 getWidth();

		u64 getHeight();

		void draw();

	private:
		TexturePtr texture;

		Transform transform;
		SpriteAlignment spriteAlignment;

		std::vector<Vertex2D_Texture> vertexes;
		std::vector<u32> indexes;
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;

		WorldMatrixBuffer worldMatrixBuffer;
		ConstantBuffer    worldMatrixBufferUploader;
	};

}