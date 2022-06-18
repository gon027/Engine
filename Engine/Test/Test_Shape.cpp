#include "../engine/include/Engine.hpp"
#include "../engine/include/EngineGraphic.hpp"
#include <include/Buffer/Buffer.hpp>
#include "../engine/include/Debug/Debug.hpp"
#include "../engine/include/Time/Time.hpp"
#include "../engine/include/2D/Rect.hpp"
#include "../engine/include/2D/Circle.hpp"

using namespace DirectX;
using namespace engine;

void gnMain() {
	App::init("A", 640, 480);
	Scene::setBackGroundColor({ 0.0f, 1.0f, 1.0f, 1.0f });

	engine::Circle rc{};

	engine::Rect r{};

	while (App::update()) {
		App::begin();

		//static float f = 0.0f;
		//f += 0.1f;

		// rc.setPosition(100, 100);
		//rc.setRotation(f);
		//rc.setScale({ 5.0f, 5.0f });
		//rc.draw();

		r.setColor({ 1.0f, 0.0f, 1.0f, 1.0f });
		r.setScale(200.0f, 200.0f);
		r.draw();
		
		App::end();
		Sleep(1);
	}
}