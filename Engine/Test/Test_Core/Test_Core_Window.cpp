/*
#include "../../engine/include/EngineMain/EngineMain.hpp"

#include "../../engine/lib/include/IWindow.hpp"
#include "../../engine/lib/src/Windows/Window.hpp"

#include <memory>

// Windows環境でのWindowテスト
void gnMain() {
	using namespace engine;

	// IWindowのポインタを作成
	std::shared_ptr<core::IWindow> window{ new engine::Window{} };
	window->init("Test IWindow", 400, 400);

	// IWindowのポインタをWindowポインタに変換(Windows用)
	{
		// Window* win = static_cast<Window*>(window.get());
		auto win = std::dynamic_pointer_cast<Window>(window);
		auto* hWnd = win->getHWnd();
		auto* hInstance = win->getHInstance();
	}

	// ウインドウの幅と高さを取得
	{
		auto width = window->getWidth();
		auto height = window->getHeight();
		std::string str{
			"width = " + std::to_string(width) + ", height = " + std::to_string(height)
		};
		OutputDebugString(str.c_str());
	}
	
	while (window->update()) {
		Sleep(1000);
		break;
	}
}
*/