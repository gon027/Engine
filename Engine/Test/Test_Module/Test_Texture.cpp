/*
#include "../../engine/include/EngineMain/EngineMain.hpp"

#include "../../engine/lib/include/IWindow.hpp"
#include "../../engine/lib/include/IDevice.hpp"
#include "../../engine/lib/include/IFactory.hpp"
#include "../../engine/lib/include/ICommandList.hpp"
#include "../../engine/lib/include/ICommandQueue.hpp"
#include "../../engine/lib/include/ISwapChain.hpp"
#include "../../engine/lib/include/DepthStencil.hpp"

#include "../../engine/include/Color/Color.hpp"

void gnMain() {
	using namespace engine;

	std::shared_ptr<core::IWindow> window = createWindow();
	if (!window->init("test", 300, 300)) {
		OutputDebugString("Windows Window Failed ... \n");
		return;
	}
	OutputDebugString("Windows Window Successed! \n");

	std::shared_ptr<core::IFactory> factory = createFactory();
	if (!factory->init()) {
		OutputDebugString("Dx12 Factory Failed ... \n");
		return;
	}
	OutputDebugString("Dx12 Factory Successed! \n");

	std::shared_ptr<core::IDevice> device = createDevice();
	if (!device->init(factory)) {
		OutputDebugString("Dx12 Device Failed ... \n");
		return;
	}
	OutputDebugString("Dx12 Device Successed! \n");

	auto adapterName = L"CurrentAdapter = " + device->getAdapterName();
	OutputDebugStringW(adapterName.c_str());

	std::shared_ptr<core::ICommandList> commandList = createCommandList();
	if (!commandList->init(device)) {
		OutputDebugString("Dx12 CommandList Failed ... \n");
		return;
	}
	OutputDebugString("Dx12 CommandList Successed! \n");

	std::shared_ptr<core::ICommandQueue> commandQueue = createCommandQueue();
	if (!commandQueue->init(device, commandList)) {
		OutputDebugString("Dx12 CommandQueue Failed ... \n");
		return;
	}
	OutputDebugString("Dx12 CommandQueue Successed! \n");

	std::shared_ptr<core::ISwapChain> swapChain = createSwapChain();
	if (!swapChain->init(window, factory, device, commandQueue)) {
		OutputDebugString("Dx12 SwapChain Failed ... \n");
		return;
	}
	OutputDebugString("Dx12 SwapChain Successed! \n");

	std::shared_ptr<core::DepthStencil> depthStencil = createDepthStencil();
	if (!depthStencil->init(window, device)) {
		OutputDebugString("Dx12 DepthStencil Failed ... \n");
		return;
	}
	OutputDebugString("Dx12 SwapChain Successed! \n");

	const ViewPort vp{ .width = 640.0f, .height = 480.0f };
	const ScissorRect sr{ .right = 640, .bottom = 480 };
	const ColorF backColor{ 1.0f, 0.3f, 1.0f, 1.0f };

	while (window->update()) {
		{
			commandList->reset();

			// �����_�[�^�[�Q�b�g���Z�b�g
			commandList->resourceBarrier(swapChain, ResouceStates::Present, ResouceStates::RenderTarget);

			// �r���[�|�[�g�ݒ�
			commandList->setViewport(vp);

			// �V�U�[��`�̐ݒ�
			commandList->setScissorRect(sr);

			// �����_�[�^�[�Q�b�g�̃N���A
			commandList->clearRenderTargetView(swapChain, backColor);

			// �����_�[�^�[�Q�b�g�̃N���A
			commandList->setRenderTargets(swapChain, depthStencil);

			// �f�v�X�X�e���V���̃N���A
			commandList->clearDepthStencilView(depthStencil);


		}

		{
			// ��ʂ̓���ւ�
			commandList->resourceBarrier(swapChain, ResouceStates::RenderTarget, ResouceStates::Present);

			commandList->close();
			commandQueue->executeCommand(commandList);

			swapChain->present();

			commandQueue->waitForPrevousFrame();
		}

		Sleep(1);
	}
}
*/