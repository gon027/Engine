#include "../../../include/EngineCore/EngineCore.hpp"
#include "../../Windows/Window.hpp"
#include "../Library/Librarys.hpp"
#include "../Device/Factory.hpp"
#include "../Device/Device.hpp"
#include "../CommandList/Dx12CommandList.hpp"
#include "../CommandList/Dx12CommandQueue.hpp"
#include "../SwapChain/Dx12SwapChain.hpp"
#include "../DepthStencil/DepthStencil.hpp"
#include <stdexcept>

namespace engine {

	EngineCore::EngineCore()
		// : window(new Window{})
		// , factory(new Dx12Factory{})
		// , device(new Dx12Device{})
		// , commandList(new Dx12CommandList{})
		// , commandQueue(new Dx12CommandQueue{})
		// , swapChain(new Dx12SwapChain{})
		: window{ createWindow() }
		, factory{ createFactory() }
		, device{ createDevice() }
		, commandList{ createCommandList() }
		, commandQueue{ createCommandQueue() }
		, swapChain{ createSwapChain() }
		, depthStencil{ createDepthStencil() }
	{
	}

	EngineCore::~EngineCore()
	{
	}

	void EngineCore::init(const std::string& _title, int _width, int _height)
	{
		if (!window->init(_title, _width, _height)) {
			throw std::runtime_error("Windows Window Initialization Failed. \n");
			return;
		}

		// デバイス類
		{
			if (!factory->init()) {
				throw std::runtime_error("Dx12 Factory Initialization Failed. \n");
				return;
			}

			if (!device->init(factory)) {
				throw std::runtime_error("Dx12 Device Initialization Failed. \n");
				return;
			}
		}

		// グラフィックス類
		{
			if (!commandList->init(device)) {
				throw std::runtime_error("Dx12 CommandList Initialization Failed. \n");
				return;
			}

			if (!commandQueue->init(device, commandList)) {
				throw std::runtime_error("Dx12 CommandQueue Initialization Failed. \n");
				return;
			}

			if (!swapChain->init(window, factory, device, commandQueue)) {
				throw std::runtime_error("Dx12 SwapChain Initialization Failed. \n");
				return;
			}

			if (!depthStencil->init(window, device)) {
				throw std::runtime_error("Dx12 DepthStencil Initialization Failed. \n");
				return;
			}
		}
	}

	void EngineCore::begin()
	{

	}

	void EngineCore::end()
	{

	}

	window_ptr EngineCore::getWindow() const
	{
		return window;
	}

	factory_ptr EngineCore::getFactory() const
	{
		return factory;
	}

	device_ptr EngineCore::getDevice() const
	{
		return device;
	}

	commandList_ptr EngineCore::getCommandList() const
	{
		return commandList;
	}

	commandQueue_ptr EngineCore::getCommandQueue() const
	{
		return commandQueue;
	}

	swapChain_ptr EngineCore::getSwapChain() const
	{
		return swapChain;
	}

	depthStencil_ptr EngineCore::getDepthStencil() const
	{
		return depthStencil;
	}
}