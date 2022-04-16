#pragma once

#include <Windows.h>

namespace engine {

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		
		case WM_SIZE: // ウインドウのサイズ変更されたときに呼ばれる
			OutputDebugString("aaaa\n");
			break;

		default:
			break;
		}

		return DefWindowProc(hwnd, msg, wp, lp);
	}

}