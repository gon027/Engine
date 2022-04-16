#pragma once

#include "Version.hpp"
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include "../Type/Type.hpp"
#include "../Input/Key.hpp"

namespace engine {

	class KeyBoard {
	private:
		static const u32 MAX_BUFFER_SIZE = 256;

	public:
		KeyBoard();
		~KeyBoard();

		bool init();

		void update();

		bool getKey(const u8 _key);

		bool getKeyDown(const u8 _key);

		bool getKeyUp(const u8 _key);

	private:
		// LPDIRECTINPUT8‚Ì‰ð•ú
		void releaseDevice();

		// LPDIRECTINPUTDEVICE8‚Ì‰ð•ú
		void releaseLpDevice();

	private:
		LPDIRECTINPUT8 device;
		LPDIRECTINPUTDEVICE8 lpDevice;

		u8 buffer[MAX_BUFFER_SIZE];
		u8 oldBuffer[MAX_BUFFER_SIZE];
	};

}