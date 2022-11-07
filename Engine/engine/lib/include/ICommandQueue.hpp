#pragma once

#include "Fwd.hpp"

namespace engine {

	namespace core {

		class ICommandQueue {
		public:
			virtual ~ICommandQueue() = default;

			virtual bool init(device_ptr _device, commandList_ptr _commandList) = 0;

			virtual void executeCommand(commandList_ptr _commandList) = 0;

			virtual void waitForPrevousFrame() = 0;
		};

	}

	std::shared_ptr<core::ICommandQueue> createCommandQueue();

}