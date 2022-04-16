// #include "EngineMain/EngineMain.hpp"
// #include "../engine/include/Window/Window.hpp"
// #include "../engine/include/EngineCore/EngineCore.hpp"
// #include "../engine/include/Graphics/Factory.hpp"
// #include "../engine/include/Graphics/Device.hpp"
// #include "../engine/include/Graphics/Adapter.hpp"

//void gnMain() {
//	using namespace engine;
//
//	engine::Window window;
//	window.init("Test", 640, 480);
//
//	window.setTitle("Gon");
//	// window.setWindowPosition(200, 500);
//
//	Factory factory{};
//	if (!factory.init()) {
//		return;
//	}
//
//	Adapter adapter{};
//	if (!adapter.init(factory())) {
//		return;
//	}
//
//	Device device{};
//	if (!device.init(factory())) {
//		return;
//	}
//
//	while (window.update()) {
//
//	}
//}