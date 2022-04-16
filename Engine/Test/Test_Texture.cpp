/*
#include "../engine/include/Engine.hpp"

void gnMain() {
	using namespace engine;

	App::init("aaa", 640, 480);

	auto tx = Texture::create(L"Test/char.png");
	Sprite sp{ };
	sp.init(tx);
	
	Image img{ 16, 16 };
	auto it = Texture::create(img);
	Sprite sp2{};
	sp2.init(it);
	sp2.setPosition({ 300, 0 });

	static float f = 0.0f;

	while (App::update()) {
		App::begin();

		f += 0.1f;

		sp.draw();
		sp.setRotation(gnLib::Quaternion::rotationAxis({ 0, 0, 1 }, f));

		sp2.draw();

		App::end();
	}
}*/