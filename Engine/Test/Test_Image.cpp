/*
#include "../engine/include/Engine.hpp"

void gnMain() {
	using namespace engine;

	App::init("A", 640, 480);
	Scene::setBackGroundColor({ 0.0f, 1.0f, 1.0f, 1.0f });

	auto imtq = Texture::create(L"Test/char.png");
	Sprite sp{};
	sp.init(imtq);

	while (App::update()) {
		App::begin();

		sp.draw();

		App::end();
	}
}
*/