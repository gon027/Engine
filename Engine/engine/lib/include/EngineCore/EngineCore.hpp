#pragma once

#include <string>
#include <memory>
#include "Common.hpp"

#define Engine()             EngineCore::get()
#define EngineWindow()       EngineCore::get()->getWindow()
#define EngineFactory()      EngineCore::get()->getFactory()
#define EngineDevice()       EngineCore::get()->getDevice()
#define EngineCommandList()  EngineCore::get()->getCommandList()
#define EngineCommandQueue() EngineCore::get()->getCommandQueue()
#define EngineSwapChain()    EngineCore::get()->getSwapChain()

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

		std::shared_ptr<core::IWindow>       getWindow() const;
		std::shared_ptr<core::IFactory>      getFactory() const;
		std::shared_ptr<core::IDevice>       getDevice() const;
		std::shared_ptr<core::ICommandList>  getCommandList() const;
		std::shared_ptr<core::ICommandQueue> getCommandQueue() const;
		std::shared_ptr<core::ISwapChain>    getSwapChain() const;

	protected:
		EngineCore();
		~EngineCore();

	private:
		EngineCore(const EngineCore&);
		EngineCore(EngineCore&&);

	private:
		std::shared_ptr<core::IWindow>       window;
		std::shared_ptr<core::IFactory>      factory;
		std::shared_ptr<core::IDevice>       device;
		std::shared_ptr<core::ICommandList>  commandList;
		std::shared_ptr<core::ICommandQueue> commandQueue;
		std::shared_ptr<core::ISwapChain>    swapChain;
	};

}