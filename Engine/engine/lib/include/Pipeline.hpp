#pragma once

#include <memory>

#include "Fwd.hpp"

namespace engine {

	struct PipelineParameter;

	namespace core {

		class Pipeline {
		public:
			virtual ~Pipeline() = default;

			virtual bool init(device_ptr _device, const PipelineParameter& _parameter) = 0;
		};

	}
}