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
#include "../../engine/include/Transform/Transform.hpp"

#include "../../engine/lib/src/Dx12/RootSignature/RootSignature.hpp"
#include "../../engine/lib/src/Dx12/PipelineState/InputLayout.hpp"

#include "../../engine/lib/src/Dx12/Shader/VertexShader.hpp"
#include "../../engine/lib/src/Dx12/Shader/PixelShader.hpp"
#include "../../engine/lib/src/Dx12/PipelineState/PipelineState.hpp"

#include "../../engine/lib/src/Dx12/Library/Librarys.hpp"
#include "../../engine/lib/src/Dx12/Device/Device.hpp"
#include "../../engine/lib/src/Dx12/CommandList/Dx12CommandList.hpp"

#include "../../engine/lib/src/Windows/Window.hpp"

#include "../../engine/include/Camera/Camera2D.hpp"
#include "../../engine/include/Camera/Camera3D.hpp"

#include "../../engine/include/Buffer/VertexBuffer.hpp"
#include "../../engine/include/Buffer/IndexBuffer.hpp"
#include "../../engine/include/Buffer/ConstantBuffer.hpp"

#include "../../engine/include/Vertex/Vertex2D.hpp"
#include "../../engine/include/IndexData/IndexData.hpp"

#include "../../engine/lib/ModelLoader/ModelImporter.hpp"
#include "../../engine/lib/ModelLoader/ModelData.hpp"

#include "../../engine/include/Input/Key.hpp"
#include "../../engine/include/Input/KeyBoard.hpp"

#include "../../engine/lib/src/Dx12/Texture/Dx12Texture.hpp"

#include "../../engine/include/Time/Time.hpp"

#include "../../engine/include/Model/Model.hpp"
#include "../../engine/include/Model/ModelPipeline.h"

using namespace engine;

void gnMain() {
	EngineCore::get()->init("test", 640, 480);
	auto window = EngineWindow();
	auto device = EngineDevice();
	auto commandList = EngineCommandList();
	auto commandQueue = EngineCommandQueue();
	auto swapChain = EngineSwapChain();
	auto depthStencil = EngineDepthStencil();
	 
	KeyBoard InKey{};
	if(!InKey.init()) return;

	Time time{};

	const size_t FIXED_FPS = 15;
	const float MIN_FRAME_TIME = 1.0f / static_cast<float>(FIXED_FPS);

	float fps = 0.0f;

	const ViewPort vp{ .width = 640.0f, .height = 480.0f };
	const ScissorRect sr{ .right = 640, .bottom = 480 };
	const ColorF backColor{ 0.0f, 0.7f, 0.7f, 1.0f };

	ModelPipeline modelPipeline{ device };

	// constant
	Camera3D cam{};
	cam.setPos({ 0.0f, 10.0f, 25.0f });

	struct CamMat {
		Matrix4x4 view;
		Matrix4x4 proj;
	} camMat{};

	camMat.view = cam.getView();
	camMat.proj = cam.getProjection();

	ConstantBuffer cameraUploader{};
	cameraUploader.init(device, &camMat, sizeof(CamMat));

	{
		// auto modelDir = "Asset/みやび式ペコリーヌ_v1.7.2/";
		// auto modelFile = "みやび式ペコリーヌ_v1.7.2.pmx";
		// ModelImporter::get()->loadModel("ぺコリーヌ", modelDir, modelFile);

		const ModelInfo yui {
			.modelDir = "Asset/Yui/",
			.modelFile = "ユイ_v1.3.pmx"
		};
		ModelImporter::get()->loadModel("ぺコリーヌ", yui);

		//auto modelDir = "Asset/misora/";
		//auto modelFile = "Misora.pmx";
		//ModelImporter::get()->loadModel("ぺコリーヌ", modelDir, modelFile);
		
		//auto modelDir = "Asset/kokkoro_ver1.01/";
		//auto modelFile = "pmx/kokkoro_ver1.01.pmx";

		//auto modelDir2 = "Asset/kokkoro_ver1.01/";
		//auto modelFile2 = "pmx/kokkoro_ver1.01.pmx";


		//auto modelDir = "Asset/フヨイカ式ユウリ配布用/";
		///auto modelFile = "フヨイカ式ユウリ_通常ver_トゥーンなし.pmx";
		// ModelImporter::get()->loadModel("kokoro", modelDir2, modelFile2);
	}
	auto peco = ModelImporter::get()->getModelData("ぺコリーヌ");
	Model pModel{ device, peco };

	{
		auto width = window->getWidth();
		auto height = window->getHeight();
		std::string str{
			"[width = " + std::to_string(width) +
			", height = " + std::to_string(height) + "]\n"
		};
		OutputDebugString(str.c_str());
	}

	while (window->update()) {
		{
			time.updateStartTime();
			InKey.update();
		}

		{
			commandList->reset();

			// レンダーターゲットをセット
			commandList->resourceBarrier(swapChain, ResouceStates::Present, ResouceStates::RenderTarget);

			// ビューポート設定 -- 
			commandList->setViewport(vp);

			// シザー矩形の設定 -- 
			commandList->setScissorRect(sr);

			// レンダーターゲットのクリア
			commandList->clearRenderTargetView(swapChain, backColor);

			// レンダーターゲットのクリア
			commandList->setRenderTargets(swapChain, depthStencil);

			// デプスステンシルのクリア
			commandList->clearDepthStencilView(depthStencil);
		}

		commandList->setRootSignature(modelPipeline.getRootSignature());
		commandList->setPipelineState(modelPipeline.getPipelineState());

		// constant
		{
			static float aaa = 0.0f;
			if (InKey.getKey(Key::A)) {
				aaa = 0.1f;
			}
			else  if (InKey.getKey(Key::D)) {
				aaa = -0.1f;
			}
			else {
				aaa = 0.0f;
			}

			static float bbb = 0.0f;
			if (InKey.getKey(Key::W)) {
				bbb = -0.1f;
			}
			else  if (InKey.getKey(Key::S)) {
				bbb = +0.1f;
				bbb = +0.1f;
			}
			else {
				bbb = 0.0f;
			}

			static float ccc = 0.0f;
			if (InKey.getKey(Key::UP)) {
				ccc = 0.1f;
			}
			else  if (InKey.getKey(Key::DOWN)) {
				ccc = -0.1f;
			}
			else {
				ccc = 0.0f;
			}

			//aaa += 0.01f;
			cam.translate(aaa, ccc, bbb);
			camMat.view = cam.getView();
			camMat.proj = cam.getProjection();
			cameraUploader.update(&camMat, sizeof(CamMat));
			commandList->setConstantBuffer(cameraUploader, 0);
		}

		pModel.update();
		pModel.draw(commandList);
		
	
		{
			// 画面の入れ替え
			commandList->resourceBarrier(swapChain, ResouceStates::RenderTarget, ResouceStates::Present);

			commandList->close();
			commandQueue->executeCommand(commandList);

			swapChain->present();

			commandQueue->waitForPrevousFrame();
		}
		
		auto frameTime = static_cast<float>(time.deltaTime()) / static_cast<float>(time.getFreq());
		if (frameTime < MIN_FRAME_TIME) {
			auto sleepTime = static_cast<DWORD>((MIN_FRAME_TIME - frameTime) * 1000);

			timeBeginPeriod(1);
			Sleep(sleepTime);
			timeEndPeriod(1);
		}
		
		fps = 1.0f / frameTime;
		window->setTitle(std::to_string(fps));
		// OutputDebugString(std::to_string(frameTime).c_str());
		// OutputDebugString("\n");

		time.updateEndTime();
	}
}
