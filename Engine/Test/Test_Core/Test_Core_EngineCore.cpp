/*
#include "../../engine/include/EngineMain/EngineMain.hpp"

#include "../../engine/lib/include/EngineCore/EngineCore.hpp"
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

	EngineCore::get()->init("test", 300, 300);
	auto window = EngineWindow();
	auto commandList = EngineCommandList();
	auto commandQueue = EngineCommandQueue();
	auto swapChain = EngineSwapChain();
	auto depthStencil = EngineDepthStencil();

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