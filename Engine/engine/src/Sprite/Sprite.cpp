#include "../../include/Sprite/Sprite.hpp"
#include "../../include/Texture/Texture.hpp"
#include "../../include/Camera/Camera2D.hpp"
// #include <include/EngineCore/EngineCore.hpp>
// #include <include/CommandList/CommandList.hpp>
// #include <include/PipelineState/RenderingPipeline2D.hpp>

namespace engine {

	/*
	namespace {
		constexpr float Size = 0.5f;

		Vector2 getPivotOffset(SpriteAlignment _spriteAlignment) {
			switch (_spriteAlignment)
			{
			case engine::SpriteAlignment::Center:
				return Vector2::Zero;
			case engine::SpriteAlignment::TopLeft:
			case engine::SpriteAlignment::TopCenter:
			case engine::SpriteAlignment::TopRight:
			case engine::SpriteAlignment::LeftCenter:
				return { -0.5f, 0.0f };
			case engine::SpriteAlignment::RightCenter:
			case engine::SpriteAlignment::BottomLeft:
			case engine::SpriteAlignment::BottomCenter:
			case engine::SpriteAlignment::BottomRight:
			default:
				return Vector2::Zero;
			}
		}
	}

	Sprite::Sprite()
		: transform()
		, spriteAlignment(SpriteAlignment::Center)
		, vertexes()
		, indexes()
		, vertexBuffer()
		, indexBuffer()
		, worldMatrixBuffer()
		, worldMatrixBufferUploader()
	{
	}

	Sprite::Sprite(TexturePtr _texture)
		: texture(_texture)
		, transform()
		, spriteAlignment(SpriteAlignment::Center)
		, vertexes()
		, indexes()
		, vertexBuffer()
		, indexBuffer()
		, worldMatrixBuffer()
		, worldMatrixBufferUploader()
	{
	}

	bool Sprite::init(TexturePtr& _texture)
	{
		setTexture(_texture);

		if (!texture) {
			return false;
		}

		vertexes.resize(4);

		float hw{ static_cast<float>(texture->getWidth()) * 0.5f };
		float hh{ static_cast<float>(texture->getHeight()) * 0.5f };
		vertexes[0] = { { -hw, -hh, 0.0f },{ 0.0f, 1.0f } };
		vertexes[1] = { { -hw,  hh, 0.0f },{ 0.0f, 0.0f } };
		vertexes[2] = { {  hw,  hh, 0.0f },{ 1.0f, 0.0f } };
		vertexes[3] = { {  hw, -hh, 0.0f },{ 1.0f, 1.0f } };

		indexes.resize(6);
		indexes[0] = 0;
		indexes[1] = 1;
		indexes[2] = 2;
		indexes[3] = 0;
		indexes[4] = 2;
		indexes[5] = 3;

		if (!vertexBuffer.init(vertexes.data(), sizeof(Vertex2DTexture), vertexes.size())) {
			return false;
		}

		if (!indexBuffer.init(indexes.data(), sizeof(u32), indexes.size())) {
			return false;
		}

		worldMatrixBuffer.world = transform.getWorldMatrix();
		worldMatrixBufferUploader.init(&worldMatrixBuffer, sizeof(WorldMatrixBuffer));

		return true;
	}

	void Sprite::setTexture(TexturePtr& _texture)
	{
		texture = _texture;
	}

	void Sprite::setAlignment(SpriteAlignment _spriteAlignment)
	{
		spriteAlignment = _spriteAlignment;
	}

	void Sprite::setTransform(const Transform& _transform)
	{
		transform = _transform;
	}

	void Sprite::setPosition(const gnLib::Vector3& _position)
	{
		transform.position = _position;
	}

	void Sprite::setRotation(const gnLib::Quaternion& _rotation)
	{
		transform.rotation = _rotation;
	}

	void Sprite::setScale(const gnLib::Vector3& _scale)
	{
		transform.scale = _scale;
	}

	u64 Sprite::getWidth()
	{
		return texture->getWidth();
	}

	u64 Sprite::getHeight()
	{
		return texture->getHeight();
	}

	void Sprite::draw()
	{
		if (!texture) {
			return;
		}

		// auto commandList = EngineCommand()->get();
		// 
		// EnginePipeline2D()->setPipeline(RenderState::Texture);
		// 
		// EngineCamera2D()->update();
		// 
		// worldMatrixBuffer.world = transform.getWorldMatrix();
		// worldMatrixBufferUploader.setConstantBuffer(1, &worldMatrixBuffer);
		// 
		// commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		// 
		// commandList->IASetVertexBuffers(0, 1, &vertexBuffer.getView());
		// commandList->IASetIndexBuffer(&indexBuffer.getView());
		// 
		// ID3D12DescriptorHeap* heaps[]{ texture->getHeap() };
		// commandList->SetDescriptorHeaps(_countof(heaps), heaps);
		// 
		// auto handle = texture->getGPUHandle();
		// commandList->SetGraphicsRootDescriptorTable(2, handle);
		// 
		// commandList->DrawIndexedInstanced((u32)indexes.size(), 1, 0, 0, 0);
	}
	*/

}