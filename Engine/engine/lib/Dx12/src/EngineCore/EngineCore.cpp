#include <include/EngineCore/EngineCore.hpp>
#include "../../../../include/Window/Window.hpp"
#include <include/Library/Librarys.hpp>
#include <include/Device/Factory.hpp>
#include <include/Device/Adapter.hpp>
#include <include/Device/Device.hpp>
#include <include/CommandList/CommandList.hpp>
#include <include/CommandList/CommandQueue.hpp>
#include <include/RenderTarget/RenderTarget.hpp>
#include <include/PipelineState/RenderingPipeline2D.hpp>
#include "../../../../include/Input/KeyBoard.hpp"
#include "../../../../include/Input/Mouse.hpp"
#include "../../../../include/Camera/Camera2D.hpp"
#include <stdexcept>

namespace engine {

	EngineCore::EngineCore()
		: window(new Window{})
		, factory(new Factory{})
		, device(new Device{})
		, commandList(new CommandList{})
		, commandQueue(new CommandQueue{})
		, renderTarget(new RenderTarget{})
		, renderingPipeline2d(new RenderingPipeline2D{})
		, keyBoard(new KeyBoard{})
		, mouse(new Mouse{})
		, camera(new Camera2D{})
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

		if (!device->init(factory.get()->get())) {
			throw std::runtime_error("Device Initialization Failed. \n");
			return;
		}

		if (!commandList->init()) {
			throw std::runtime_error("CommandList Initialization Failed. \n");
			return;
		}

		if (!commandQueue->init()) {
			throw std::runtime_error("CommandQueue Initialization Failed. \n");
			return;
		}

		if (!renderTarget->init()) {
			throw std::runtime_error("RenderTarget Initialization Failed. \n");
			return;
		}

		renderingPipeline2d->init();

		if (!keyBoard->init()) {
			throw std::runtime_error("KeyBoard Initialization Failed. \n");
			return;
		}

		if (!mouse->init()) {
			throw std::runtime_error("Mouse Initialization Failed. \n");
			return;
		}

		if (!camera->init()) {
			throw std::runtime_error("Camera2D Initialization Failed. \n");
			return;
		}

	}

	void EngineCore::begin()
	{
		commandList->reset();

		renderTarget->setRenderTargetView(D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

		renderTarget->clearScreen();
		renderTarget->setRenderTargets();

		keyBoard->update();
		mouse->update();
	}

	void EngineCore::end()
	{
		renderTarget->setRenderTargetView(D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

		commandList->close();

		commandQueue->executeCommand();

		renderTarget->present();

		commandQueue->waitForPrevousFrame();

		renderTarget->swapCurrentBackBufferIndex();
	}

	Window* EngineCore::getWindow() const
	{
		return window.get();
	}

	Factory* EngineCore::getFactory() const
	{
		return factory.get();
	}

	Device* EngineCore::getDevice() const
	{
		return device.get();
	}

	CommandList* EngineCore::getCommandList() const
	{
		return commandList.get();
	}

	CommandQueue* EngineCore::getCommandQueue() const
	{
		return commandQueue.get();
	}

	RenderTarget* EngineCore::getRenderTarget() const
	{
		return renderTarget.get();
	}

	RenderingPipeline2D* EngineCore::getRenderingPipeline2D() const
	{
		return renderingPipeline2d.get();
	}

	KeyBoard* EngineCore::getKeyBoard() const
	{
		return keyBoard.get();
	}

	Mouse* EngineCore::getMouse() const
	{
		return mouse.get();
	}

	Camera2D* EngineCore::getCamera2D() const
	{
		return camera.get();
	}
}