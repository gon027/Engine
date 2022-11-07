/*
#include "../../engine/include/EngineMain/EngineMain.hpp"

#include "../../engine/lib/include/IWindow.hpp"
#include "../../engine/lib/src/Windows/Window.hpp"

#include <memory>

// Windows���ł�Window�e�X�g
void gnMain() {
	using namespace engine;

	// IWindow�̃|�C���^���쐬
	std::shared_ptr<core::IWindow> window{ new engine::Window{} };
	window->init("Test IWindow", 400, 400);

	// IWindow�̃|�C���^��Window�|�C���^�ɕϊ�(Windows�p)
	{
		// Window* win = static_cast<Window*>(window.get());
		auto win = std::dynamic_pointer_cast<Window>(window);
		auto* hWnd = win->getHWnd();
		auto* hInstance = win->getHInstance();
	}

	// �E�C���h�E�̕��ƍ������擾
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