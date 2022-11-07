#pragma once

#include "Fwd.hpp"

namespace engine {

	namespace core {
		class DepthStencil {
		public:
			virtual ~DepthStencil() = default;

			virtual bool init(window_ptr _window, device_ptr _device) = 0;
		};
	}

	std::shared_ptr<core::DepthStencil> createDepthStencil();

}