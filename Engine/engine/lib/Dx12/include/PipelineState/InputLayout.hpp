#pragma once

#include <vector>
#include "../../include/Library/Librarys.hpp"

namespace engine {

	class InputLayout {
	public:
		InputLayout(std::initializer_list<D3D12_INPUT_ELEMENT_DESC> _elements);
		~InputLayout();

		inline D3D12_INPUT_LAYOUT_DESC getInputLayout() {
			return {
				elements.data(),
				static_cast<UINT>(elements.size())
			};
		}

	private:
		std::vector<D3D12_INPUT_ELEMENT_DESC> elements;
	};

}