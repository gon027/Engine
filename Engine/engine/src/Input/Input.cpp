#include "../../include/Input/Input.hpp"
// #include "../../lib/src/Dx12/include/EngineCore/EngineCore.hpp"
#include "../../include/Input/Mouse.hpp"
#include "../../include/Input/KeyBoard.hpp"

namespace engine {

	namespace Input {

		bool getKey(u8 _key)
		{
			//return EngineKeyBoard()->getKey(_key);
			return false;

		}

		bool getKeyDown(u8 _key)
		{
			//return EngineKeyBoard()->getKeyDown(_key);
			return false;
		}

		bool getKeyUp(u8 _key)
		{
			//return EngineKeyBoard()->getKeyUp(_key);
			return false;

		}

		bool getMouseButton(MouseType _mouseType)
		{
			//return EngineMouse()->getMouseButton(_mouseType);
			return false;

		}

		bool getMouseButtonDown(MouseType _mouseType)
		{
			//return EngineMouse()->getMouseButtonDown(_mouseType);
			return false;

		}

		bool getMouseButtonUp(MouseType _mouseType)
		{
			//return EngineMouse()->getMouseButtonUp(_mouseType);
			return false;

		}

	}

}