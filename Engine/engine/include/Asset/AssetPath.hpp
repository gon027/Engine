#pragma once

#include <string>

namespace engine {

	struct ShaderPath {
		static inline const std::wstring Path = L"engine/lib/shader/";
	};

	template <class A>
	inline std::string AssetPath(const std::string& _path) {
		return A::Path + _path;
	}

	template <class A>
	inline std::wstring AssetPath(const std::wstring& _path) {
		return A::Path + _path;
	}
}