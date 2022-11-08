#pragma once

#include <string>
#include <memory>
#include "Common.hpp"
#include "../Fwd.hpp"

#define Engine()             EngineCore::get()
#define EngineWindow()       EngineCore::get()->getWindow()
#define EngineFactory()      EngineCore::get()->getFactory()
#define EngineDevice()       EngineCore::get()->getDevice()
#define EngineCommandList()  EngineCore::get()->getCommandList()
#define EngineCommandQueue() EngineCore::get()->getCommandQueue()
#define EngineSwapChain()    EngineCore::get()->getSwapChain()
#define EngineDepthStencil() EngineCore::get()->getDepthStencil()

namespace engine {

	namespace core {
		class IWindow;
		class IFactory;
		class IDevice;
		class ICommandList;
		class ICommandQueue;
		class ISwapChain;
	}

	class EngineCore : public Singleton<EngineCore> {
        friend Singleton<EngineCore>;

	public:
		void init(const std::string& _title, int _width, int _height);

		void begin();

		void end();

		window_ptr       getWindow() const;
		factory_ptr      getFactory() const;
		device_ptr       getDevice() const;
		commandList_ptr  getCommandList() const;
		commandQueue_ptr getCommandQueue() const;
		swapChain_ptr    getSwapChain() const;
		depthStencil_ptr getDepthStencil() const;

	protected:
		EngineCore();
		~EngineCore();

	private:
		EngineCore(const EngineCore&);
		EngineCore(EngineCore&&);

	private:
		window_ptr       window;
		factory_ptr      factory;
		device_ptr       device;
		commandList_ptr  commandList;
		commandQueue_ptr commandQueue;
		swapChain_ptr    swapChain;
		depthStencil_ptr depthStencil;
	};

}