/*
#include "../engine/include/EngineMain/EngineMain.hpp"
#include "../engine/include/EngineCore/EngineCore.hpp"
#include "../engine/include/Window/Window.hpp"
#include "../engine/include/Graphics/Device.hpp"
#include "../engine/include/Graphics/CommandList.hpp"
#include "../engine/include/Graphics/RenderingPipeline2D.hpp"
#include "../engine/include/MatrixBuffer/MatrixBuffer.hpp"
#include "../engine/include/Graphics/ConstantBuffer.hpp"
#include "../engine/include/Mesh/Mesh.hpp"
#include "../engine/include/Engine.hpp"
using namespace engine;
#include <vector>

void gnMain() {
	using namespace engine;

	try {
		Engine()->init("aaa ", 640, 480);
	}
	catch (const std::exception&) {
		return;
	}

	Image img{ 128, 128 };
	for (size_t y = 0; y < img.getHeight(); ++y) {
		for (size_t x = 0; x < img.getRowPitch(); x += img.getStride()) {
			img.setPixel(x, y, { 0xFF, 0xFF, 0xFF, 0xFF });
		}
	}

	auto imtq = Texture::create(L"Test/char.png");
	auto imt = Texture::create(img.getData(), img.getWidth(), img.getHeight(), img.getStride());
	Sprite sp{}, sp2{};
	sp.init(imt);
	sp2.init(imtq);

	float x = 0.0f;
	while (EngineWindow()->update()) {
		Engine()->begin();

		sp.setRotation(Quaternion::rotationAxis({ 0, 0, 1 }, x));
		sp.draw();

		x += 0.05f;
		//sp2.setPosition({ 100 * sinf(x), 0, 0 });
		//sp2.draw();

		Engine()->end();
		Sleep(1);
	}

}
*/
