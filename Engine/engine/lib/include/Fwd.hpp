#pragma once

#include <memory>

namespace engine {

	class Resource;

	namespace core {
		class IWindow;
		class IFactory;
		class IDevice;
		class ICommandList;
		class ICommandQueue;
		class ISwapChain;
		class ITexture;
	}

	using window_ptr       = std::shared_ptr<core::IWindow>;
	using factory_ptr      = std::shared_ptr<core::IFactory>;
	using device_ptr       = std::shared_ptr<core::IDevice>;
	using commandList_ptr  = std::shared_ptr<core::ICommandList>;
	using commandQueue_ptr = std::shared_ptr<core::ICommandQueue>;
	using swapChain_ptr    = std::shared_ptr<core::ISwapChain>;
	using texture_ptr      = std::shared_ptr<core::ITexture>;
	using resource_ptr     = std::shared_ptr<Resource>;
}