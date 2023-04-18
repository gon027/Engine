#include "ModelImporter.hpp"

#include "PMD/PMDFile.hpp"
#include "PMX/PMXFile.hpp"
#include "ModelLoader.hpp"
#include "PMD/PMDLoader.hpp"
#include "PMX/PMXLoader.hpp"

namespace {

	template <class String>
	String getExtension(const String& _path) {
		auto findIdx = _path.rfind(L'.');
		auto extension = _path.substr(findIdx + 1, _path.size() - 1);

		return extension;
	}

	// PMDの形式からModelDataの形式に変換
	void convertPMDToModelData(ModelDataPtr& _modelData, const model::pmd::PMDFile& _pmdFile) {

		_modelData->extension = "pmd";
		_modelData->modelName = _pmdFile.header.modelName;

		{
			size_t vertexSize = _pmdFile.vertexes.size();
			_modelData->vertexes.resize(vertexSize);
			for (size_t i{ 0 }; i < vertexSize; ++i) {
				std::memcpy(_modelData->vertexes[i].position, _pmdFile.vertexes[i].position, sizeof(_pmdFile.vertexes[i].position));
				std::memcpy(_modelData->vertexes[i].normal, _pmdFile.vertexes[i].normal, sizeof(_pmdFile.vertexes[i].normal));
				std::memcpy(_modelData->vertexes[i].uv, _pmdFile.vertexes[i].uv, sizeof(float[2]));
			}
		}

		{
			size_t indexSize = _pmdFile.indexes.size();
			_modelData->indexes.resize(indexSize);
			std::copy(_pmdFile.indexes.begin(), _pmdFile.indexes.end(), _modelData->indexes.begin());
		}

		{
			size_t materialSize = _pmdFile.materials.size();
			_modelData->materials.resize(materialSize);
			for (size_t i{ 0 }; i < materialSize; ++i) {

				std::string textureStr{ _pmdFile.materials[i].textureFileName };
				// TODO: もう少し処理を最適化する
				if (textureStr[textureStr.size() - 1] == '/') { // パスの最後の文字が/なら、画像へのパスがないので追加する
					_modelData->materials[i].textureName = _modelData->materials[i - 1].textureName;
				}
				else {
					// スフィアマップを取り除く
					auto idx = textureStr.find('*');
					if (idx != std::string::npos) {
						textureStr = textureStr.substr(0, idx);
					}

					_modelData->materials[i].textureName = textureStr;
				}
				_modelData->materials[i].vertCount = _pmdFile.materials[i].faceVertCount;
			}
		}
	}

	// PMXの形式からModelDataの形式に変換
	void convertPMXToModelData(ModelDataPtr& _modelData, const model::pmx::PMXFile& _pmxFile) {
		_modelData->extension = "pmx";
		_modelData->modelName = _pmxFile.modelInfo.modelName;

		{
			size_t vertexSize = _pmxFile.vertexes.size();
			_modelData->vertexes.resize(vertexSize);
			for (size_t i{ 0 }; i < vertexSize; ++i) {
				std::memcpy(_modelData->vertexes[i].position, _pmxFile.vertexes[i].position, sizeof(float[3]));
				std::memcpy(_modelData->vertexes[i].normal, _pmxFile.vertexes[i].normal, sizeof(float[3]));
				std::memcpy(_modelData->vertexes[i].uv, _pmxFile.vertexes[i].uv, sizeof(float[2]));
			}
		}

		{
			size_t indexSize = _pmxFile.indexes.size();
			_modelData->indexes.resize(indexSize);
			std::copy(_pmxFile.indexes.begin(), _pmxFile.indexes.end(), _modelData->indexes.begin());
		}

		{
			size_t materialSize = _pmxFile.materials.size();
			_modelData->materials.resize(materialSize);
			for (size_t i{ 0 }; i < materialSize; ++i) {
				auto textureIndex = _pmxFile.materials[i].normalTextureIndex;

				_modelData->materials[i].textureName = _pmxFile.textures[textureIndex];
				_modelData->materials[i].vertCount = _pmxFile.materials[i].surface;


				std::memcpy(_modelData->materials[i].material.diffuse, _pmxFile.materials[i].diffuse, sizeof(_pmxFile.materials[i].diffuse));
				std::memcpy(_modelData->materials[i].material.specular, _pmxFile.materials[i].specular, sizeof(_pmxFile.materials[i].specular));
				_modelData->materials[i].material.specularCoefficient = _pmxFile.materials[i].specularCoefficient;
				std::memcpy(_modelData->materials[i].material.ambient, _pmxFile.materials[i].ambient, sizeof(_pmxFile.materials[i].ambient));
				
			}
		}

		// スフィアテクスチャのセット
		{
			size_t materialSize = _pmxFile.materials.size();
			for (size_t i{ 0 }; i < materialSize; ++i) {
				_modelData->materials[i].sphereMode = _pmxFile.materials[i].mode;

				auto sphereIndex = _pmxFile.materials[i].sphereTextureIndex;

				if (sphereIndex != 0xff) {
					_modelData->materials[i].sphereName = _pmxFile.textures[sphereIndex];
				}
			}
		}

		// トゥーンテクスチャのセット
		{
			size_t materialSize = _pmxFile.materials.size();
			for (size_t i{ 0 }; i < materialSize; ++i) {
				auto toonIndex = _pmxFile.materials[i].indexSize;

				if (toonIndex != 0xff) {
					_modelData->materials[i].toonName = _pmxFile.textures[toonIndex];
				}
			}
		}

	}
}

ModelImporter::ModelImporter()
	: modelList()
{
}

void ModelImporter::loadModel(const std::string& _name, const std::string& _modelDir, const std::string& _modelFile)
{
	std::string extension = getExtension(_modelFile);

	if (extension == "pmd") {
		model::pmd::PMDLoader pmdLoader{};
		pmdLoader.load(_modelDir, _modelFile);

		ModelDataPtr modelData{ new model::ModelData{} };
		convertPMDToModelData(modelData, pmdLoader.getFile());

		modelList.emplace(_name, modelData);
	}

	if (extension == "pmx") {
		model::pmx::PMXLoader pmxLoader{};
		pmxLoader.load(_modelDir, _modelFile);

		ModelDataPtr modelData{ new model::ModelData{} };
		convertPMXToModelData(modelData, pmxLoader.getFile());

		modelList.emplace(_name, modelData);
	}

}

void ModelImporter::loadModel(const std::string& _name, const ModelInfo& _modelInfo)
{
	loadModel(_name, _modelInfo.modelDir, _modelInfo.modelFile);
}

ModelDataPtr ModelImporter::getModelData(const std::string& _name)
{
	if (!modelList.contains(_name)) {
		return nullptr;
	}

	return modelList[_name];
}

ModelDataPtr ModelImporter::getModelData(const std::string& _name, const std::string& _modelDir, const std::string& _modelFile)
{
	if (!modelList.contains(_name)) {
		loadModel(_name, _modelDir, _modelFile);
	}

	return modelList[_name];
}
