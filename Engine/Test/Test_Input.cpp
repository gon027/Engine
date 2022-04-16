// #include "EngineMain/EngineMain.hpp"
// #include "../engine/include/EngineCore/EngineCore.hpp"
// #include "../engine/include/Window/Window.hpp"
// #include "../engine/include/Type/Type.hpp"
// 
// #include "../engine/include/Input/KeyBoard.hpp"
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
//
//	KeyBoard keyBoard{};
//	if (!keyBoard.init()) {
//		return;
//	}
//
//	int frame{ 0 };
//	float time{ 0.0f };
//
//	while (EngineWindow()->update()) {
//
//		keyBoard.update();
//
//		if (keyBoard.getKeyDown(Key::A)) {
//			EngineWindow()->resizeWindow(256, 256);
//		}
//
//		if (keyBoard.getKeyDown(Key::D)) {
//			EngineWindow()->resizeWindow(640, 480);
//		}
//
//		// if (keyBoard.getKey(Key::A)) {
//		// 	EngineWindow()->setTitle("a");
//		// }
//
//		// if (keyBoard.getKeyUp(Key::A)) {
//		// 	EngineWindow()->setTitle("");
//		// }
//
//		++frame;
//		time += 0.01f;
//
//		Sleep(1);
//	}
//}

//#define SAFERELEASE(_p) if(_p) _p->Release(); _p = nullptr;
//
//#define DIRECTINPUT_VERSION 0x0800
//
//#include <dinput.h>
//
//#pragma comment(lib, "dinput8.lib")
//#pragma comment(lib, "dxguid.lib")
//
//constexpr u8 KEY_A = DIK_A;
//constexpr u8 KEY_D = DIK_D;
//constexpr u8 KEY_Q = DIK_Q;
//
//void outputAddress(const std::string& _name, void* _p) {
//	long address = (long)(&_p);
//	std::string out{ _name + " Pointer = " + std::to_string(address) + '\n'};
//	OutputDebugString(out.c_str());
//}
//
//void gnMain() {
//	using namespace engine;
//
//	Window window{};
//	window.init("Input_Test", 320, 240);
//
//	LPDIRECTINPUT8 device{ nullptr };
//	LPDIRECTINPUTDEVICE8 lpDevice{ nullptr };
//	
//	constexpr u32 MAX_BUFFER_SIZE = 256;
//	u8 buffer[MAX_BUFFER_SIZE];
//
//	HRESULT hr{};
//	hr = DirectInput8Create(
//		window.getHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&device, NULL
//	);
//	if (FAILED(hr)) {
//		return;
//	}
//
//	hr = device->CreateDevice(GUID_SysKeyboard, &lpDevice, nullptr);
//	if (FAILED(hr)) {
//		return;
//	}
//
//	hr = lpDevice->SetDataFormat(&c_dfDIKeyboard);
//	if (FAILED(hr)) {
//		return;
//	}
//
//	hr = lpDevice->SetCooperativeLevel(
//		window.getHWnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY
//	);
//	if (FAILED(hr)) {
//		return;
//	}
//
//	lpDevice->Acquire();
//
//	while (window.update()) {
//		ZeroMemory(buffer, sizeof(buffer));
//		HRESULT hr = lpDevice->GetDeviceState(sizeof(buffer), buffer);
//		// std::string s{ "RESULT = " + std::to_string((long)hr) + '\n' };
//		// OutputDebugString(s.c_str());
//		if (hr == DIERR_INPUTLOST) {
//			lpDevice->Acquire();
//		}
//
//		// outputAddress("Window", &window);
//		// outputAddress("Device", &device);
//		// outputAddress("LPDevice", &lpDevice);
//
//		if (buffer[KEY_A] & 0x80) {
//			window.setTitle("A");
//		}
//
//		if (buffer[KEY_D] & 0x80) {
//			window.setTitle("D");
//		}
//
//		if (buffer[KEY_Q] & 0x80) {
//			break;
//		}
//
//		Sleep(1);
//	}
//  
//  // デバイスの解放を入れる 
//	SAFERELEASE(device);
//	SAFERELEASE(lpDevice);
//}

