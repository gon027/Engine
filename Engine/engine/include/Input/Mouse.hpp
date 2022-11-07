#pragma once

#include "Version.hpp"
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include "MouseType.hpp"
#include "../Type/Type.hpp"

namespace engine {

	struct MousePosition {
		int x;
		int y;
	};

	class Mouse {
	public:
		Mouse();
		~Mouse();

		bool init();

		void update();

		bool getMouseButton(MouseType _mouseType);

		bool getMouseButtonDown(MouseType _mouseType);

		bool getMouseButtonUp(MouseType _mouseType);

		MousePosition getMousePosition();

	private:
		// LPDIRECTINPUT8‚Ì‰ð•ú
		void releaseDevice();

		// LPDIRECTINPUTDEVICE8‚Ì‰ð•ú
		void releaseLpDevice();

	private:
		LPDIRECTINPUT8 device;
		LPDIRECTINPUTDEVICE8 lpDevice;

		DIMOUSESTATE currentState;
		DIMOUSESTATE prevState;
	};

}