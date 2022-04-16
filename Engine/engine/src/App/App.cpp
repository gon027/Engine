#include "../../include/App/App.hpp"
#include "../../include/EngineCore/EngineCore.hpp"
#include "../../include/Window/Window.hpp"

namespace engine {

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
}