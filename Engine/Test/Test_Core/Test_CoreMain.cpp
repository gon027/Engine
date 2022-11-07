/*
#include "../../engine/include/EngineMain/EngineMain.hpp"

// ‚±‚¿‚ç‚ÍŽÀ‘•ƒNƒ‰ƒX
#include "../../engine/lib/Windows/Window.hpp"
#include "../../engine/lib/Dx12/include/Device/Device.hpp"
#include "../../engine/lib/Dx12/include/Device/Factory.hpp"
#include "../../engine/lib/Dx12/include/CommandList/CommandList.hpp"
#include "../../engine/lib/Dx12/include/CommandList/CommandQueue.hpp"

#include "../../engine/lib/Viewport.hpp"
#include "../../engine/lib/ScissorRect.hpp"

void gnMain() {
	using namespace engine;

	std::shared_ptr<IWindow> window{ new Window{} };
	if (window->init("test", 300, 300)) {
		OutputDebugString("Window Yes.\n");
	}

	std::shared_ptr<core::IFactory> factory{ new Dx12Factory{} };
	if (factory->init()) {
		OutputDebugString("Factory Yes.\n");
	}

	std::shared_ptr<core::IDevice> device{ new Dx12Device{} };
	if (device->init(factory.get())) {
		OutputDebugString("Device Yes.\n");
	}

	std::shared_ptr<core::ICommandList> commandList{ new Dx12CommandList{} };
	if (commandList->init(device.get())) {
		OutputDebugString("CommandList Yes.\n");
	}

	std::shared_ptr<core::ICommandQueue> commandQueue{ new Dx12CommandQueue{} };
	if (commandQueue->init(device.get(), commandList.get())) {
		OutputDebugString("CommandQueue Yes.\n");
	}

	// ViewPort vp{ .width = 640.0f, .height = 480.0f };
	// ScissorRect sr{ .right = 640, .bottom = 480 };

	

	while (window->update()) {
		{
			commandList->reset();
		}

		{

		}


		{
			commandList->close();

			commandQueue->executeCommand(commandList.get());

			commandQueue->waitForPrevousFrame();
		}

		Sleep(1);
	}
}
*/