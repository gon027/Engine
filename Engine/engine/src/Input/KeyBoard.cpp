#include "../../include/Input/KeyBoard.hpp"

#include "../../lib/include/EngineCore/EngineCore.hpp"
#include "../../lib/src/Windows/Window.hpp"

namespace engine {

	namespace {

		constexpr u32 PUSH_VALUE = 0x80;

		bool isPush(u8 _keyValue) {
			return _keyValue & PUSH_VALUE;
		}

	}

	KeyBoard::KeyBoard()
		: device(nullptr)
		, lpDevice(nullptr)
		, buffer()
		, oldBuffer()
	{
	}

	KeyBoard::~KeyBoard()
	{
		releaseDevice();
		releaseLpDevice();
	}

	bool KeyBoard::init()
	{
		HRESULT hr{};

		auto window = EngineWindow();

		hr = DirectInput8Create(
			(HINSTANCE)window->getInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&device, NULL
		);
		if (FAILED(hr)) {
			releaseDevice();
			return false;
		}

		hr = device->CreateDevice(GUID_SysKeyboard, &lpDevice, nullptr);
		if (FAILED(hr)) {
			releaseDevice();
			releaseLpDevice();
			return false;
		}

		hr = lpDevice->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(hr)) {
			releaseDevice();
			releaseLpDevice();
			return false;
		}

		hr = lpDevice->SetCooperativeLevel(
			(HWND)window->getHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY
		);
		if (FAILED(hr)) {
			releaseDevice();
			releaseLpDevice();
			return false;
		}

		lpDevice->Acquire();

		return true;
	}

	void KeyBoard::update()
	{
		ZeroMemory(buffer, sizeof(buffer));

		HRESULT hr = lpDevice->GetDeviceState(sizeof(buffer), buffer);
		if (hr == DIERR_INPUTLOST) {
			lpDevice->Acquire();
			lpDevice->GetDeviceState(sizeof(buffer), buffer);
		}
	}

	bool KeyBoard::getKey(const u8 _key)
	{
		bool result = false;

		if (isPush(buffer[_key]) && isPush(oldBuffer[_key])) {
			result = true;
		}

		oldBuffer[_key] = buffer[_key];

		return result;
	}

	bool KeyBoard::getKeyDown(const u8 _key)
	{
		bool result = false;

		if (isPush(buffer[_key]) && !isPush(oldBuffer[_key])) {
			result = true;
		}

		oldBuffer[_key] = buffer[_key];

		return result;
	}

	bool KeyBoard::getKeyUp(const u8 _key)
	{
		bool result = false;

		if (!isPush(buffer[_key]) && isPush(oldBuffer[_key])) {
			result = true;
		}

		oldBuffer[_key] = buffer[_key];

		return result;
	}

	void KeyBoard::releaseDevice()
	{
		if (device) {
			device->Release();
			device = nullptr;
		}
	}

	void KeyBoard::releaseLpDevice()
	{
		if (lpDevice) {
			lpDevice->Unacquire();
			lpDevice->Release();
			lpDevice = nullptr;
		}
	}
}