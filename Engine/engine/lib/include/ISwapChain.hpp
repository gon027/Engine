#pragma once

#include <memory>
#include "Fwd.hpp"
#include "../../../engine/include/Core/ResourceOption.hpp"

namespace engine {

	namespace core {

		class ISwapChain {
		public:
			virtual ~ISwapChain() = default;

			virtual bool init(
				window_ptr _window, factory_ptr _factory, device_ptr _device, commandQueue_ptr _commandQueue
			) = 0;

			virtual void present() = 0;
		};

	}

	std::shared_ptr<core::ISwapChain> createSwapChain();

}