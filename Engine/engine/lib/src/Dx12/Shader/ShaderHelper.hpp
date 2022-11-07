#pragma once

#include <string>
#include "../Library/Librarys.hpp"

namespace engine {

	inline D3DBlob compileShader(const std::wstring& _fileName, const std::string& _entryPoint, const std::string _target) {

		UINT compileFlags{ 0 };
#if defined(_DEBUG)
		compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif // defined(_DEBUG)

		D3DBlob result{ nullptr };
		HRESULT hr = D3DCompileFromFile(
			_fileName.c_str(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			_entryPoint.c_str(),
			_target.c_str(),
			compileFlags,
			0,
			&result,
			nullptr
		);

		if (FAILED(hr)) {
			return nullptr;
		}

		return result;
	}

}