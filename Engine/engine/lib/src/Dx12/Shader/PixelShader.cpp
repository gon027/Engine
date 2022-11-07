#include "PixelShader.hpp"
#include "ShaderHelper.hpp"

namespace engine {

	PixelShader::PixelShader(const std::wstring& _fileName, const std::string& _entryPoint, const std::string _target)
		: shader(nullptr)
	{
		shader = compileShader(_fileName, _entryPoint, _target);
	}

}