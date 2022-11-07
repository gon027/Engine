#include "../../include/App/App.hpp"
// #include "../../include/Window/IWindow.hpp"
// #include "../../include/Color/Color.hpp"
// #include <include/EngineCore/EngineCore.hpp>
// #include <include/RenderTarget/RenderTarget.hpp>
#include <string_view>

namespace engine {

	/*
	namespace App {

		void init(const std::string& _title, int _width, int _height)
		{
			using namespace engine;

			try {
				Engine()->init(_title, _width, _height);
			}
			catch (const std::exception& _e) {
				OutputDebugString(_e.what());
				return;
			}
		}

		void begin()
		{
			Engine()->begin();
		}

		bool update()
		{
			return EngineWindow()->update();
		}

		void end()
		{
			Engine()->end();
		}
	}

	namespace Scene {

		void Scene::setBackGroundColor(const ColorF& _color)
		{
			EngineRenderTarget()->setBackBroundColor(_color);
		}

		void setWindowTitie(std::string_view _title)
		{
			EngineWindow()->setTitle(_title.data());
		}

	}
	*/
}


