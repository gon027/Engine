#pragma once

#include <string>

namespace engine {

	namespace App {

		void init(const std::string& _title, int _width, int _height);

		void begin();

		bool update();

		void end();

	}

}