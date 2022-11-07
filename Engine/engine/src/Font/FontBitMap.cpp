/*#include "..\..\include\Font\FontBitMap.hpp"
#include "../../include/Font/GlyphData.hpp"

namespace engine {

	namespace {
		template <class Character>
		UINT getCharCode(const Character* _c) {
#if _UNICODE

			return static_cast<UINT>(*_c);
#else
			UINT code{ 0 };
			BYTE testChar{ static_cast<BYTE>(*_c) };

			// マルチバイト文字の場合
			bool isMultiByte = IsDBCSLeadByte(testChar);
			if (isMultiByte) {
				code = (BYTE)_c[0] << 8 | (BYTE)_c[1];
			}
			else {
				code = _c[0];
			}

			return code;
#endif
		}

		GlyphData getGlyphData(HDC& _hdc, const wchar_t* _c) {
			// 文字コード取得
			UINT code = getCharCode(_c);

			// フォントのビットマップ作成
			TEXTMETRIC tm{};
			GetTextMetrics(_hdc, &tm);

			GLYPHMETRICS gm{};
			const MAT2 mat{ {0, 1},{0, 0}, {0, 0}, {0, 1} };

			const DWORD size{
				GetGlyphOutline(_hdc, code, GGO_GRAY4_BITMAP, &gm, 0, NULL, &mat)
			};

			if (size == GDI_ERROR) {
				return {};
			}

			unsigned char* ptr{ new unsigned char[size] };
			GetGlyphOutline(_hdc, code, GGO_GRAY4_BITMAP, &gm, size, ptr, &mat);

			return {
				gm.gmCellIncX,
				tm.tmHeight,
				tm.tmAscent,
				tm.tmDescent,
				gm.gmptGlyphOrigin.x,
				gm.gmptGlyphOrigin.y,
				gm.gmBlackBoxX,
				gm.gmBlackBoxY,
				ptr
			};
		}

		UINT getGradLevel(int _gradFlag) {
			switch (_gradFlag)
			{
			case GGO_GRAY2_BITMAP: return 4;
			case GGO_GRAY4_BITMAP: return 16;
			case GGO_GRAY8_BITMAP: return 64;
			}

			return 16;
		}

	}

	FontBitMap::FontBitMap(const std::string& _fontName, int _fontSize)
		: hdc()
		, hFont()
		, oldFont()
	{
		auto* fn = _fontName.c_str();
		LOGFONT lf{
			_fontSize,
			0,
			0,
			0,
			300,
			0,
			0,
			0,
			SHIFTJIS_CHARSET,
			OUT_TT_ONLY_PRECIS,
			CLIP_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_MODERN,
			*fn
		};

		hFont = CreateFontIndirect(&lf);
		if (!hFont) {
			return;  // 失敗
		}

		// デバイスコンテキスト取得
		hdc = GetDC(NULL);
		oldFont = (HFONT)SelectObject(hdc, hFont);
	}

	FontBitMap::~FontBitMap()
	{
		// デバイスコンテキストとフォントハンドルの開放
		SelectObject(hdc, oldFont);
		DeleteObject(hFont);
		ReleaseDC(NULL, hdc);
	}

	std::shared_ptr<Image> FontBitMap::getFontBitMap(wchar_t* _c)
	{
		auto g = getGlyphData(hdc, _c);

		struct FontRect {
			size_t xStart;
			size_t yStart;
			size_t xEnd;
			size_t yEnd;
		};

		FontRect r{
			.xStart = static_cast<size_t>(g.glyphOriginX),
			.yStart = static_cast<size_t>(g.ascent - g.glyphOriginY),
			.xEnd = static_cast<size_t>(g.blackBoxX + (4 - (g.blackBoxX % 4)) % 4),
			.yEnd = static_cast<size_t>(g.blackBoxY)
		};

		const int gradFlag = GGO_GRAY4_BITMAP;
		UINT level = getGradLevel(gradFlag);

		std::shared_ptr<Image> img{ new Image{(u64)((g.cellIncX + 3) / 4 * 4), (u64)g.height} };
		for (size_t y{ r.yStart }; y < r.yStart + r.yEnd; ++y) {
			for (size_t x{ r.xStart }; x < r.xStart + r.xEnd; ++x) {
				const size_t index = x - (size_t)(r.xStart) + (size_t)(r.xEnd) * (y - (size_t)(r.yStart));
				const DWORD value = g.ptr[index];

				const DWORD alpha = (255 * value) / level;
				const DWORD color = 0x00FFFFFF | (alpha << 24);

				ColorI ci{ color };
				img->setPixel(img->getRowPitch() * y + 4 * x, ci);
			}
		}

		if (g.ptr) {
			delete[] g.ptr;
			g.ptr = nullptr;
		}

		return img;
	}

}
*/