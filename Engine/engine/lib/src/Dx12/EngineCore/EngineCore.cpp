#include "../../../include/EngineCore/EngineCore.hpp"
#include "../../Windows/Window.hpp"
#include "../Library/Librarys.hpp"
#include "../Device/Factory.hpp"
#include "../Device/Device.hpp"
#include "../CommandList/Dx12CommandList.hpp"
#include "../CommandList/Dx12CommandQueue.hpp"
#include "../SwapChain/Dx12SwapChain.hpp"
#include <stdexcept>

namespace engine {

	EngineCore::EngineCore()
		: window(new Window{})
		, factory(new Dx12Factory{})
		, device(new Dx12Device{})
		, commandList(new Dx12CommandList{})
		, commandQueue(new Dx12CommandQueue{})
		, swapChain(new Dx12SwapChain{})
	{
	}

	EngineCore::~EngineCore()
	{
	}

	void EngineCore::init(const std::string& _title, int _width, int _height)
	{
		if (!window->init(_title, _width, _height)) {
			throw std::runtime_error("Window Initialization Failed. \n");
			return;
		}

		if (!factory->init()) {
			throw std::runtime_error("Factory Initialization Failed. \n");
			return;
		}

		if (!device->init(factory)) {
			throw std::runtime_error("Device Initialization Failed. \n");
			return;
		}

		if (!commandList->init(device)) {
			throw std::runtime_error("CommandList Initialization Failed. \n");
			return;
		}

		if (!commandQueue->init(device, commandList)) {
			throw std::runtime_error("CommandQueue Initialization Failed. \n");
			return;
		}

		if (!swapChain->init(window, factory, device, commandQueue)) {
			throw std::runtime_error("SwapChain Initialization Failed. \n");
			return;
		}
	}

	void EngineCore::begin()
	{

	}

	void EngineCore::end()
	{

	}

	std::shared_ptr<core::IWindow> EngineCore::getWindow() const
	{
		return window;
	}

	std::shared_ptr<core::IFactory> EngineCore::getFactory() const
	{
		return factory;
	}

	std::shared_ptr<core::IDevice> EngineCore::getDevice() const
	{
		return device;
	}

	std::shared_ptr<core::ICommandList> EngineCore::getCommandList() const
	{
		return commandList;
	}

	std::shared_ptr<core::ICommandQueue> EngineCore::getCommandQueue() const
	{
		return commandQueue;
	}

	std::shared_ptr<core::ISwapChain> EngineCore::getSwapChain() const
	{
		return swapChain;
	}
}