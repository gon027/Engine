#include "InputLayout.hpp"

namespace engine {

	InputLayout::InputLayout(std::initializer_list<InputElement> _elements)
		: elements(_elements)
		, elementSize(elements.size())
	{
	}

	InputLayout::~InputLayout()
	{
	}

}