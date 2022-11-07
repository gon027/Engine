/*
#include "../../include/Font/Font.hpp"
#include "../../include/Font/GlyphData.hpp"
#include "../../include/Image/Image.hpp"
#include "../../include/Texture/Texture.hpp"
#include <tchar.h>

#include <ios>
#include <fstream>
#include <iomanip> 
#include <bitset>

namespace engine {

	Font::Font(const std::string& _fontName, int _fontSize)
		: position(Vector2::Zero)
		, scale(Vector3::One)
		, quaternion(0.0f, 0.0f, 0.0f, 1.0f)
		, fontBitMap(_fontName, _fontSize)
	{
	}

	Font::~Font()
	{
	}

	void Font::setPosition(float _x, float _y, float _z)
	{
		position.set(_x, _y, _z);
	}

	void Font::setPosition(const Vector3& _pos)
	{
		position = _pos;
	}

	void Font::setScale(const Vector3& _scale)
	{
		scale = _scale;
	}

	void Font::draw(const std::wstring& _text)
	{
		drawSprites.clear();

		for (auto _c : _text) {
			auto t = getCharacterResource(_c);

			std::shared_ptr<Sprite> s{ new Sprite };
			s->init(t);
			drawSprites.emplace_back(s);
		}

		float offset = 0.0f;
		for (auto& _sp : drawSprites) {
			offset += static_cast<float>(_sp->getWidth());
			_sp->setPosition({ offset + position.x, 0 + position.y, 0 + position.z });
			_sp->setScale(scale);
			_sp->draw();
		}
	}

	TexturePtr Font::getCharacterResource(wchar_t _c)
	{
		if (textureMap.contains(_c)) {
			return textureMap[_c];
		}

		auto a = fontBitMap.getFontBitMap(&_c);

		auto t = Texture::create(*a);
		textureMap.emplace(_c, t);

		return textureMap[_c];
	}

	std::shared_ptr<Sprite> Font::getSprite(TexturePtr _t)
	{
		if (spriteMap.contains(_t)) {
			return spriteMap[_t];
		}

		std::shared_ptr<Sprite> sp{ new Sprite };
		sp->init(_t);
		spriteMap.emplace(_t, sp);

		return spriteMap[_t];;
	}

}
*/