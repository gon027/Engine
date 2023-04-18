#include "Model.hpp"

#include "../../lib/ModelLoader/ModelData.hpp"

#include "../../lib/src/Dx12/Device/Device.hpp"
#include "../../lib/src/Dx12/CommandList/Dx12CommandList.hpp"

#include "../../lib/ModelLoader/PMX/PMXDataStruct.hpp"

#include "../Image/Image.hpp"

namespace engine {

	Model::Model(device_ptr _device, ModelDataPtr _model)
		: modelData(_model)
		, transform({})
		, vertexBuffer()
		, indexBuffer()
		, constantBuffer()
		, textures()
		, materials()
	{
		assert(_device != nullptr);
		assert(modelData != nullptr);

		auto* device = static_cast<Dx12Device*>(_device.get());

		vertexBuffer.init(
			_device, modelData->vertexes.data(), sizeof(model::ModelData::ModelVertex), modelData->vertexes.size()
		);

		indexBuffer.init(
			_device, modelData->indexes.data(), sizeof(unsigned int), modelData->indexes.size()
		);

		auto world = transform.getWorldMatrix();
		constantBuffer.init(_device, &world, sizeof(world));

		// テクスチャ読み込み
		const auto materialSize = _model->materials.size();
		{
			for (auto i{ 0 }; i < materialSize; ++i) {
				auto textureName = std::get<std::wstring>(_model->materials[i].textureName);
				if (textures.contains(textureName)) {
					continue;
				}

				Dx12Texture texture{};
				texture.load(_device, textureName);
				textures[textureName] = std::move(texture);
			}
		}
		// マテリアルの定数バッファ
		{
			for (auto i{ 0 }; i < materialSize; ++i) {
				auto textureName = std::get<std::wstring>(_model->materials[i].textureName);
				if (materials.contains(textureName)) {
					continue;
				}

				ConstantBuffer csb{};
				csb.init(_device, &_model->materials[i].material, sizeof(_model->materials[i].material));
				materials[textureName] = std::move(csb);
			}
		}

		// Sphere Texture作成
		{
			for (auto i{ 0 }; i < materialSize; ++i) {

				
				if (std::holds_alternative<std::string>(_model->materials[i].sphereName)) {
					auto sphereMode = _model->materials[i].sphereMode;
					if (sphereMode == model::pmx::SphereMode::Addition) {
						Image img{ 2, 2 };
						Dx12Texture texture{};
						texture.load(_device, img);
						textures[L"Null_WhiteTexture"] = std::move(texture);
					}
				}


				// 空文字の場合
				if (!std::holds_alternative<std::string>(_model->materials[i].sphereName)) {

					auto textureName = std::get<std::wstring>(_model->materials[i].sphereName);
					if (textures.contains(textureName)) {
						continue;
					}

			
					Dx12Texture texture{};
					if (textureName != L"") {
						texture.load(_device, textureName);
						textures[textureName] = std::move(texture);
						continue;
					}
			


				}

				/*
				Dx12Texture texture{};
				auto sphereMode = _model->materials[i].sphereMode;
				if (sphereMode == model::pmx::SphereMode::Addition) {
					Image img{ 2, 2, WhiteTexture };
					texture.load(_device, img);
					textures[L"Null_WhiteTexture"] = std::move(texture);
				}
				else if (sphereMode == model::pmx::SphereMode::Multiply) {
					Image img{ 2, 2, WhiteTexture };
					texture.load(_device, img);
					textures[L"Null_BlackTexture"] = std::move(texture);
				}
				*/
			}
		}
	}

	Model::~Model()
	{
	}

	void Model::update()
	{
		static float angle = 3.14f;
		angle += 0.1f;

		transform.rotation = gnLib::Quaternion::rotationAxis({ 0.0f, 1.0f, 0.0f }, angle);
	}

	void Model::draw(commandList_ptr _cmdList)
	{
		auto world = transform.getWorldMatrix();
		constantBuffer.update(&world, sizeof(world));
		_cmdList->setConstantBuffer(constantBuffer, 1);

		_cmdList->setPrimitiveTopology();
		_cmdList->setVertexBuffer(vertexBuffer);
		_cmdList->setIndexBuffer(indexBuffer);


		auto offset{ 0 };
		for (auto index{ 0 }; index < modelData->materials.size(); ++index) {
			auto textureName = std::get<std::wstring>(modelData->materials[index].textureName);
			

			_cmdList->setConstantBuffer(materials[textureName], 2);

			{
				ID3D12DescriptorHeap* heaps[]{ textures[textureName].getHeap() };
				_cmdList->setDescriptorHeaps(_countof(heaps), heaps);

				auto handle = textures[textureName].getHeap()->GetGPUDescriptorHandleForHeapStart();
				_cmdList->setGraphicsRootDescriptorTable(3, handle);
			}

			{
				if (!std::holds_alternative<std::string>(modelData->materials[index].sphereName)) {
					auto spherename = std::get<std::wstring>(modelData->materials[index].sphereName);
					ID3D12DescriptorHeap* sheaps[]{ textures[spherename].getHeap() };
					//_cmdList->setDescriptorHeaps(_countof(sheaps), sheaps);

					//auto handle = textures[spherename].getHeap()->GetGPUDescriptorHandleForHeapStart();
					//_cmdList->setGraphicsRootDescriptorTable(4, handle);
				}
			}

			auto count = modelData->materials[index].vertCount;
			_cmdList->drawIndexedInstanced(count, 1, offset, 0, 0);

			offset += count;
		}
	}

	void Model::setPosition(const Vector3& _pos)
	{
		transform.position = _pos;
	}


}
