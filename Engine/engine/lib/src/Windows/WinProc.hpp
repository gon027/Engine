#pragma once

/*
#include <Windows.h>

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_win32.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);


namespace engine {

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		
		case WM_SIZE: // �E�C���h�E�̃T�C�Y�ύX���ꂽ�Ƃ��ɌĂ΂��
			OutputDebugString("aaaa\n");
			break;

		default:
			break;
		}


		ImGui_ImplWin32_WndProcHandler(hwnd, msg, wp, lp);

		return DefWindowProc(hwnd, msg, wp, lp);
	}

}
*/