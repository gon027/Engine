#include "Dx12ShaderManager.hpp"
#include "Dx12Shader.hpp"

namespace engine {
 
	
	Dx12Shader Dx12ShaderManager::addVertex(const ShaderInfo& _shaderInfo)
	{
		if (vertexList.contains(_shaderInfo.name)) {
			return vertexList.at(_shaderInfo.name);
		}

		Dx12Shader shader{ _shaderInfo.fileName, _shaderInfo.entryPoint, _shaderInfo.target };
		vertexList.emplace(_shaderInfo.name, shader);
		return vertexList.at(_shaderInfo.name);
	}

	Dx12Shader Dx12ShaderManager::addPixel(const ShaderInfo& _shaderInfo)
	{
		if (pixelList.contains(_shaderInfo.name)) {
			return pixelList.at(_shaderInfo.name);
		}

		Dx12Shader shader{ _shaderInfo.fileName, _shaderInfo.entryPoint, _shaderInfo.target };
		pixelList.emplace(_shaderInfo.name, shader);
		return pixelList.at(_shaderInfo.name);
	}

	/*
	Dx12Shader Dx12ShaderManager::getVertex(ShaderInfo _shaderInfo)
	{
		return Dx12Shader();
	}

	Dx12Shader Dx12ShaderManager::getPixel(ShaderInfo _shaderInfo)
	{
		return Dx12Shader();
	}
	*/
}