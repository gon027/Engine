#include "../engine/include/Engine.hpp"
#include "../engine/include/Font/Font.hpp"

void gnMain() {
	using namespace engine;

	App::init("aaa", 640, 480);

	Font f("‚l‚r ‚o–¾’©", 64);

	int frame = 0;
	while (App::update()) {
		App::begin();
	
		std::wstring str = (L"aiueoa");
		f.draw(str.c_str());
	
		++frame;
		App::end();
		Sleep(1);
	}
}