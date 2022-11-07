#pragma once

#include "Fwd.hpp"

namespace engine::core {

	class RenderTarget {
	public:
		virtual ~RenderTarget() = default;

		virtual bool init(
			window_ptr _window, factory_ptr  _factory, device_ptr _device,
			commandList_ptr _commandList, commandQueue_ptr  commansQueue
		) = 0;
	};

}