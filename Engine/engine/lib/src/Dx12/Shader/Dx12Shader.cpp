#include "Dx12Shader.hpp"
#include "ShaderHelper.hpp"

namespace engine {

	Dx12Shader::Dx12Shader(
		const std::wstring& _fileName, const std::string& _entryPoint, const std::string _target
	)
		: shader(nullptr)
	{
		shader = compileShader(_fileName, _entryPoint, _target);
	}

}