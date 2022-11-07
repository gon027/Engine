#pragma once

#include <string>
#include <unordered_map>
#include "../PipelineState/PipelineState.hpp"
#include "../../../include/EngineCore/Common.hpp"

namespace engine {

	class Dx12Shader;

	class Dx12ShaderManager : public Singleton<Dx12ShaderManager> {
		friend Singleton<Dx12ShaderManager>;

	public:

		Dx12Shader addVertex(const ShaderInfo& _shaderInfo);

		Dx12Shader addPixel(const ShaderInfo& _shaderInfo);

		Dx12Shader addGeometry(const ShaderInfo& _shaderInfo);

		Dx12Shader addHull(const ShaderInfo& _shaderInfo);

		Dx12Shader addDomain(const ShaderInfo& _shaderInfo);

		Dx12Shader getVertex(const ShaderInfo& _shaderInfo);

		Dx12Shader getPixel(const ShaderInfo& _shaderInfo);

		Dx12Shader getGeometry(const ShaderInfo& _shaderInfo);

		Dx12Shader getHull(const ShaderInfo& _shaderInfo);

		Dx12Shader getDomain(const ShaderInfo& _shaderInfo);

	private:
		std::unordered_map<std::string, Dx12Shader> vertexList;
		std::unordered_map<std::string, Dx12Shader> pixelList;
		std::unordered_map<std::string, Dx12Shader> geometryList;
		std::unordered_map<std::string, Dx12Shader> hullList;
		std::unordered_map<std::string, Dx12Shader> domainList;
	};

}