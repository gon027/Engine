#pragma once

#include "Key.hpp"
#include "MouseType.hpp"

namespace engine {

	namespace Input {

		bool getKey(u8 _key);

		bool getKeyDown(u8 _key);

		bool getKeyUp(u8 _key);

		bool getMouseButton(MouseType _mouseType);

		bool getMouseButtonDown(MouseType _mouseType);

		bool getMouseButtonUp(MouseType _mouseType);

	}

}