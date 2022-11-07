#pragma once

#include <string>
#include "../Library/Librarys.hpp"

namespace engine {

	class Dx12Shader {
	public:
		Dx12Shader(
			const std::wstring& _fileName, const std::string& _entryPoint, const std::string _target
		);
		~Dx12Shader() = default;

		inline D3D12_SHADER_BYTECODE getByteCode() const {
			return {
				reinterpret_cast<UINT8*>(shader->GetBufferPointer()),
				shader->GetBufferSize()
			};
		}

	private:
		D3DBlob shader;
	};

}