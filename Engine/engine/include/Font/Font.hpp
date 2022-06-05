#pragma once

#include <Windows.h>

#include <string>
#include <vector>
#include <unordered_map>

#include "../Sprite/Sprite.hpp"
#include "../Texture/Texture.hpp"
#include "../Image/Image.hpp"
#include "FontBitMap.hpp"

namespace engine {

	class Font {
	public:
		Font(const std::string& _fontName, int _fontSize);
		~Font();

		void setPosition(float _x, float _y, float _z);
		void setPosition(const Vector3& _pos);

		void setScale(float _x, float _y, float _z);
		void setScale(const Vector3& _scale);

		void setRotation(float _x, float _y, float _z);
		
		void draw(const std::wstring& _text);

	private:
		TexturePtr getCharacterResource(wchar_t _c);
		std::shared_ptr<Sprite> getSprite(TexturePtr _t);

	private:
		FontBitMap fontBitMap;

		Vector3 position;
		Vector3 scale;
		Quaternion quaternion;

		std::unordered_map<wchar_t, TexturePtr> textureMap;
		std::unordered_map<TexturePtr, std::shared_ptr<Sprite>> spriteMap;

		std::vector<std::shared_ptr<Sprite>> drawSprites;

	};

}