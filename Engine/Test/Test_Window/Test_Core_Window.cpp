/*
#include "../../engine/lib/include/IWindow.hpp"
// #include "../../engine/lib/src/Windows/Window.hpp"
// #include <memory>

// WindowsŠÂ‹«‚Å‚ÌWindowƒeƒXƒg
void gnMain() {
	using namespace engine;

	// std::shared_ptr<core::IWindow> window{ new engine::Window{} };
	auto window = engine::createWindow();
	window->init("Test IWindow", 400, 400);
	
	while (window->update()) {
		// Sleep(1);
	}
}
*/