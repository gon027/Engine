#include "../../engine/lib/include/IWindow.hpp"
#include "../../engine/lib/src/Windows/Window.hpp"

// Windows���ł�Window�e�X�g
void gnMain() {
	using namespace engine;

	std::shared_ptr<core::IWindow> window{ new engine::Window{} };
	window->init("Test IWindow", 400, 400);

	// ���T�C�Y
	window->resizeWindow(640, 480);

	// �ړ�
	window->setWindowPosition(100, 100);

	while (window->update()) {
		Sleep(1);
	}
}