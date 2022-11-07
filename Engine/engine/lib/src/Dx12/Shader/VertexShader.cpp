#include "VertexShader.hpp"
#include "ShaderHelper.hpp"

namespace engine {

	VertexShader::VertexShader(const std::wstring& _fileName, const std::string& _entryPoint, const std::string _target)
		: shader(nullptr)
	{
		shader = compileShader(_fileName, _entryPoint, _target);
	}


}