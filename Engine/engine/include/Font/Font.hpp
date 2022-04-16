#pragma once

#include <Windows.h>

#include <string>
#include <vector>
#include <unordered_map>

#include "../Sprite/Sprite.hpp"
#include "../Texture/Texture.hpp"

namespace engine {

	class Font {
	public:
		Font(const std::string& _fontName, int _fontSize);
		~Font();
		
		void draw(const std::wstring& _text);

	private:
		TexturePtr getCharacterResource(wchar_t _c);
		std::shared_ptr<Sprite> getSprite(TexturePtr _t);

	private:
		HDC hdc;
		HFONT hFont;
		HFONT oldFont;

		std::unordered_map<wchar_t, TexturePtr> textureMap;
		std::unordered_map<TexturePtr, std::shared_ptr<Sprite>> spriteMap;

		std::vector<std::shared_ptr<Sprite>> drawSprites;

	};

}