#include "../../include/Input/Input.hpp"
#include <include/EngineCore/EngineCore.hpp>
#include "../../include/Input/Mouse.hpp"
#include "../../include/Input/KeyBoard.hpp"

namespace engine {

	namespace Input {

		bool getKey(u8 _key)
		{
			return EngineKeyBoard()->getKey(_key);
		}

		bool getKeyDown(u8 _key)
		{
			return EngineKeyBoard()->getKeyDown(_key);
		}

		bool getKeyUp(u8 _key)
		{
			return EngineKeyBoard()->getKeyUp(_key);
		}

		bool getMouseButton(MouseType _mouseType)
		{
			return EngineMouse()->getMouseButton(_mouseType);
		}

		bool getMouseButtonDown(MouseType _mouseType)
		{
			return EngineMouse()->getMouseButtonDown(_mouseType);
		}

		bool getMouseButtonUp(MouseType _mouseType)
		{
			return EngineMouse()->getMouseButtonUp(_mouseType);
		}

	}

}