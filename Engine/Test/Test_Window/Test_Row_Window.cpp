#include "../../engine/lib/include/IWindow.hpp"
#include "../../engine/lib/src/Windows/Window.hpp"

// Windows環境でのWindowテスト
void gnMain() {
	using namespace engine;

	std::shared_ptr<core::IWindow> window{ new engine::Window{} };
	window->init("Test IWindow", 400, 400);

	// リサイズ
	window->resizeWindow(640, 480);

	// 移動
	window->setWindowPosition(100, 100);

	while (window->update()) {
		Sleep(1);
	}
}