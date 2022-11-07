#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "ModelData.hpp"
#include "../include/EngineCore/Common.hpp"

using ModelDataPtr = std::shared_ptr<model::ModelData>;
using ModelList = std::unordered_map<std::string, ModelDataPtr>;

class ModelImporter : public engine::Singleton<ModelImporter> {
	friend Singleton<ModelImporter>;

public:
	void loadModel(const std::string& _name, const std::string& _modelDir, const std::string& _modelFile);

	ModelDataPtr getModelData(const std::string& _name);

	ModelDataPtr getModelData(const std::string& _name, const std::string& _modelDir, const std::string& _modelFile);

protected:
	ModelImporter();

private:
	ModelList modelList;
};