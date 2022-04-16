// #include "EngineMain/EngineMain.hpp"
// #include "../engine/include/Window/Window.hpp"
// #include "../engine/include/EngineCore/EngineCore.hpp"
// #include "../engine/include/Graphics/Factory.hpp"
// #include "../engine/include/Graphics/Device.hpp"
// #include "../engine/include/Graphics/CommandList.hpp"
// 
// #include "../engine/include/Graphics/ConstantBuffer.hpp"
// 
// #include <vector>

/*
struct Buffer {
	float x, y, z;
};

void gnMain() {
	using namespace engine;

	try {
		Engine()->init();
	}
	catch (const std::exception&) {
		return;
	}

	Buffer cb{ 1, 2, 3 };

	ConstantBuffer cBuffer{ sizeof(Buffer) };

	while (EngineWindow()->update()) {
		cb.x += 1.0f;
		cBuffer.update(&cb, sizeof(cb));

		Sleep(1);
	}

	
}
*/