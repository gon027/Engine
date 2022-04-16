// #include "EngineMain/EngineMain.hpp"
// #include "../engine/include/EngineCore/EngineCore.hpp"
// #include "../engine/include/Window/Window.hpp"
// #include "../engine/include/Type/Type.hpp"
// 
// #include "../engine/include/Input/Mouse.hpp"
//
//void gnMain() {
//	using namespace engine;
//
//	try {
//		Engine()->init();
//	}
//	catch (const std::exception&) {
//		return;
//	}
//
//	Mouse mouse{};
//	if (!mouse.init()) {
//		return;
//	}
//
//	u32 frame{ 0 };
//
//	while (EngineWindow()->update()) {
//		mouse.update();
//
//		// if (mouse.getMouseButton(MouseType::Left)) {
//		// 	EngineWindow()->setTitle(std::to_string(frame));
//		// }
//		// 
//		// if (mouse.getMouseButton(MouseType::Middle)) {
//		// 	EngineWindow()->setTitle(std::to_string(frame));
//		// }
//		// 
//		// if (mouse.getMouseButton(MouseType::Right)) {
//		// 	EngineWindow()->setTitle(std::to_string(frame));
//		// }
//
//		// if (mouse.getMouseButtonDown(MouseType::Left)) {
//		// 	EngineWindow()->setTitle("getMouseButtonDown::Left");
//		// }
//		// 
//		// if (mouse.getMouseButtonDown(MouseType::Middle)) {
//		// 	EngineWindow()->setTitle("getMouseButtonDown::Middle");
//		// }
//		// 
//		// if (mouse.getMouseButtonDown(MouseType::Right)) {
//		// 	EngineWindow()->setTitle("getMouseButtonDown::Right");
//		// }
//
//		// if (mouse.getMouseButtonUp(MouseType::Left)) {
//		// 	EngineWindow()->setTitle("getMouseButtonUp::Left");
//		// }
//		// 
//		// if (mouse.getMouseButtonUp(MouseType::Middle)) {
//		// 	EngineWindow()->setTitle("getMouseButtonUp::Middle");
//		// }
//		// 
//		// if (mouse.getMouseButtonUp(MouseType::Right)) {
//		// 	EngineWindow()->setTitle("getMouseButtonUp::Right");
//		// }
//
//		if (mouse.getMouseButton(MouseType::Left)) {
//			EngineWindow()->resizeWindow(256, 256);
//		}
//
//		auto p = mouse.getMousePosition();
//		std::string str{
//			"x = " + std::to_string(p.x) +
//			", y = " + std::to_string(p.y) + '\n'
//		};
//		EngineWindow()->setTitle(str.c_str());
//
//		++frame;
//		Sleep(1);
//	}
//
//
//}

/*
#define SAFERELEASE(_p) if(_p) _p->Release(); _p = nullptr;

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

void gnMain() {
	using namespace engine;

	Window window{};
	window.init("Input_Test", 320, 240);

	LPDIRECTINPUT8 device{ nullptr };
	LPDIRECTINPUTDEVICE8 lpDevice{ nullptr };
	
	DIMOUSESTATE mouseState;

	HRESULT hr{};
	hr = DirectInput8Create(
		window.getHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&device, NULL
	);
	if (FAILED(hr)) {
		return;
	}

	hr = device->CreateDevice(GUID_SysMouse, &lpDevice, nullptr);
	if (FAILED(hr)) {
		return;
	}

	hr = lpDevice->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr)) {
		return;
	}

	hr = lpDevice->SetCooperativeLevel(
		window.getHWnd(),DISCL_NONEXCLUSIVE | DISCL_FOREGROUND
	);
	if (FAILED(hr)) {
		return;
	}

	DIPROPDWORD prop;
	prop.diph.dwSize = sizeof(DIPROPDWORD);
	prop.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	prop.diph.dwHow = DIPH_DEVICE;
	prop.diph.dwObj = 0;
	prop.dwData = DIPROPAXISMODE_REL;
	hr = lpDevice->SetProperty(DIPROP_AXISMODE, &prop.diph);
	if (FAILED(hr)) {
		return;
	}

	lpDevice->Acquire();

	while (window.update()) {

		hr = lpDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState);
		std::string d{
			"hr = " + std::to_string(hr) + '\n'
		};
		OutputDebugString(d.c_str());
		if (hr == DIERR_INPUTLOST) {
			lpDevice->Acquire();
			// lpDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState);
		}

		if (mouseState.rgbButtons[0] & 0x80) {
			window.setTitle("a");
		}

		std::string out{
			"lX = " + std::to_string(mouseState.lX) +
			", lY = " + std::to_string(mouseState.lY) + 
			", lZ = " + std::to_string(mouseState.lZ) + '\n'
		};
		window.setTitle(out.c_str());

		Sleep(1);
	}

	SAFERELEASE(device);
	SAFERELEASE(lpDevice);
}
*/