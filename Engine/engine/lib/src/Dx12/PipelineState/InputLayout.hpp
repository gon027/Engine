#pragma once

#include <vector>
#include <string>
#include "../Library/Librarys.hpp"
#include "../../../engine/include/Core/ResourceOption.hpp"

namespace engine {

	struct InputElement {
		std::string semanticName;
		engine::TextureFormat format;
	};

	class InputLayout {
	public:
		InputLayout(std::initializer_list<InputElement> _elements);
		~InputLayout();

		const InputElement& getElement(size_t _index) {
			return elements[_index];
		}

		const unsigned int getSize() const {
			return elementSize;
		}

	private:
		std::vector<InputElement> elements;
		unsigned int elementSize;
	};

}