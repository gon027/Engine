#pragma once
#include <memory>

namespace engine {

	struct GlyphData {
		int cellIncX;            // 文字全体の幅
		int height;              // 文字全体の高さ
		int ascent;              // 文字のベースラインから一番上まで 
		int descent;             // 文字のベースラインから一番下まで 
		int glyphOriginX;        // 文字の開始位置のX座標	    
		int glyphOriginY;        // 文字の開始位置のY座標
		unsigned int blackBoxX;  // 文字の横幅
		unsigned int blackBoxY;  // 文字の縦幅
		unsigned char* ptr;      // データ
	};

}