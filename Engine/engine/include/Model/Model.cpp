#include "Model.hpp"

#include "../../lib/ModelLoader/ModelData.hpp"

#include "../../lib/src/Dx12/Device/Device.hpp"

namespace engine {

	namespace {

		std::wstring convertStringToWString(const std::string& _str) {
			size_t len = _str.size();  // 文字列の長さ
			size_t convLen;            // 変換後文字列

			// 文字列の格納場所
			wchar_t* wc = new wchar_t[sizeof(wchar_t) * (len + 2)];
			mbstowcs_s(&convLen, wc, len + 1, _str.c_str(), _TRUNCATE);

			std::wstring res{ wc };
			delete[] wc;

			return res;
		}
	}

	Model::Model(device_ptr _device, ModelDataPtr _model)
		: modelData(_model)
		, transform({})
		, vertex()
		, index()
		, vertexBuffer()
		, indexBuffer()
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

		/*
		// リソースビューの設定
		{
			std::vector<std::wstring> textureName;

			{
				auto textureSize = modelData->materials.size();

				// std::unordered_set<std::wstring> textureName;
				std::unordered_map<std::wstring, size_t> temps;

				size_t off{ 0 };
				for (size_t i{ 0 }; i < textureSize; ++i) {
					auto t = modelData->materials[i].textureName;

					std::wstring wstr;
					{
						if (std::holds_alternative<std::string>(t)) {
							auto a = std::get<std::string>(t);
							wstr = convertStringToWString(a);
						}

						if (std::holds_alternative<std::wstring>(t)) {
							wstr = std::get<std::wstring>(t);
						}
					}

					//if (!textureName.contains(wstr)) { // 画像が登録されていない場合
						//textureName.emplace(wstr);

					auto itr = std::find(textureName.begin(), textureName.end(), wstr);
					if (itr == textureName.end()) {
						textureName.emplace_back(wstr);

						TextureResource::getIns()->addTexture(wstr, _device);

						temps[wstr] = off;

						offsets.push_back(off);
						++off;
					}
					else {
						offsets.push_back(temps[wstr]);
					}
				}
			}

			{
				auto textureSize = modelData->materials.size();

				// シェーダと定数バッファのDescriptor Heapを作成
				D3D12_DESCRIPTOR_HEAP_DESC dhDesc{};
				dhDesc.NumDescriptors = (UINT)(textureSize);
				dhDesc.NodeMask = 0;
				dhDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
				dhDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
				auto hr = device->get()->CreateDescriptorHeap(&dhDesc, IID_PPV_ARGS(srvDescHeap.GetAddressOf()));
				if (FAILED(hr)) {
					// return false;
				}

				incrimentSize = device->get()->GetDescriptorHandleIncrementSize(
					D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV
				);

				size_t i{ 0 };
				for (auto& ws : textureName) {

					auto& d = TextureResource::getIns()->getTexture(ws, _device);

					// シェーダリソースビューの作成
					D3D12_SHADER_RESOURCE_VIEW_DESC desc{};
					desc.Format = d.getResource()->GetDesc().Format;
					desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
					desc.Texture2D.MipLevels = d.getResource()->GetDesc().MipLevels;
					desc.Texture2D.MostDetailedMip = 0;
					desc.Texture2D.PlaneSlice = 0;
					desc.Texture2D.ResourceMinLODClamp = 0.0f;
					desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

					auto cpuHandle = srvDescHeap->GetCPUDescriptorHandleForHeapStart();
					cpuHandle.ptr += incrimentSize * i;
					device->get()->CreateShaderResourceView(d.getResource(), &desc, cpuHandle);

					++i;

				}
			}
		}
		*/
	}

	Model::~Model()
	{
	}

}
