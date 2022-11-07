#include "../../include/Input/Mouse.hpp"
// #include "../../lib/src/Dx12/include/EngineCore/EngineCore.hpp"
#include "../../lib/src/Windows/Window.hpp"

namespace engine {

	namespace {

		constexpr u32 PUSH_VALUE = 0x80;

		bool isPush(u8 _mouseValue) {
			return _mouseValue & PUSH_VALUE;
		}

	}

	Mouse::Mouse()
		: device(nullptr)
		, lpDevice(nullptr)
		, currentState({})
		, prevState({})
	{
	}

	Mouse::~Mouse()
	{
		releaseDevice();
		releaseLpDevice();
	}

	bool Mouse::init()
	{
		HRESULT hr{};
		/*
		auto* window = static_cast<Window*>(EngineWindow());
		hr = DirectInput8Create(
			window->getHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&device, NULL
		);
		if (FAILED(hr)) {
			return false;
		}

		hr = device->CreateDevice(GUID_SysMouse, &lpDevice, nullptr);
		if (FAILED(hr)) {
			return false;
		}

		hr = lpDevice->SetDataFormat(&c_dfDIMouse);
		if (FAILED(hr)) {
			return false;
		}

		hr = lpDevice->SetCooperativeLevel(
			window->getHWnd(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND
		);
		if (FAILED(hr)) {
			return false;
		}

		DIPROPDWORD prop;
		prop.diph.dwSize = sizeof(DIPROPDWORD);
		prop.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		prop.diph.dwHow = DIPH_DEVICE;
		prop.diph.dwObj = 0;
		prop.dwData = DIPROPAXISMODE_REL;
		hr = lpDevice->SetProperty(DIPROP_AXISMODE, &prop.diph);
		if (FAILED(hr)) {
			return false;
		}

		lpDevice->Acquire();
		*/

		return true;
	}

	void Mouse::update()
	{
		HRESULT hr = lpDevice->GetDeviceState(sizeof(DIMOUSESTATE), &currentState);
		if (hr == DIERR_INPUTLOST) {
			lpDevice->Acquire();
			lpDevice->GetDeviceState(sizeof(DIMOUSESTATE), &currentState);
		}
	}

	bool Mouse::getMouseButton(MouseType _mouseType)
	{
		bool result = false;

		const u32 idx = static_cast<u32>(_mouseType);
		if (isPush(currentState.rgbButtons[idx]) && isPush(prevState.rgbButtons[idx])) {
			result = true;
		}

		prevState.rgbButtons[idx] = currentState.rgbButtons[idx];

		return result;
	}

	bool Mouse::getMouseButtonDown(MouseType _mouseType)
	{
		bool result = false;

		const u32 idx = static_cast<u32>(_mouseType);
		if (isPush(currentState.rgbButtons[idx]) && !isPush(prevState.rgbButtons[idx])) {
			result = true;
		}

		prevState.rgbButtons[idx] = currentState.rgbButtons[idx];

		return result;
	}

	bool Mouse::getMouseButtonUp(MouseType _mouseType)
	{
		bool result = false;

		const u32 idx = static_cast<u32>(_mouseType);
		if (!isPush(currentState.rgbButtons[idx]) && isPush(prevState.rgbButtons[idx])) {
			result = true;
		}

		prevState.rgbButtons[idx] = currentState.rgbButtons[idx];

		return result;
	}

	MousePosition Mouse::getMousePosition()
	{
		POINT mousePoint{};

		// 座標を取得
		GetCursorPos(&mousePoint);

		// マウス座標をクライアント座標に変換
		//auto* window = static_cast<Window*>(EngineWindow());
		//ScreenToClient(window->getHWnd(), &mousePoint);

		return {
			mousePoint.x,
			mousePoint.y
		};
	}

	void Mouse::releaseDevice()
	{
		if (device) {
			device->Release();
			device = nullptr;
		}
	}

	void Mouse::releaseLpDevice()
	{
		if (lpDevice) {
			lpDevice->Unacquire();
			lpDevice->Release();
			lpDevice = nullptr;
		}
	}
}