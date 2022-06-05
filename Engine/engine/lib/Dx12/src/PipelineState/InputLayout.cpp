#include <include/PipelineState/InputLayout.hpp>

namespace engine {

	InputLayout::InputLayout(std::initializer_list<D3D12_INPUT_ELEMENT_DESC> _elements)
		: elements(_elements)
	{
	}

	InputLayout::~InputLayout()
	{
	}

}