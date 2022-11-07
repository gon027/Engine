#pragma once

#include <string>

namespace engine {

	struct ColorF;

	namespace App {

		void init(const std::string& _title, int _width, int _height);

		void begin();

		bool update();

		void end();

	}

	namespace Scene {

		void setBackGroundColor(const ColorF& _color);

		void setWindowTitie(std::string_view _title);

	}

}