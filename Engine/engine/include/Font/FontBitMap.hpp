#pragma once

#include <Windows.h>

#include <string>
#include <vector>
#include <memory>

#include "../Image/Image.hpp"

namespace engine {

	class FontBitMap {
	public:
		FontBitMap(const std::string& _fontName, int _fontSize);
		~FontBitMap();

		std::shared_ptr<Image> getFontBitMap(wchar_t* _c);

	private:
		HDC hdc;
		HFONT hFont;
		HFONT oldFont;
	};

}