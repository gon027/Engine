/*
#include "../../engine/include/EngineMain/EngineMain.hpp"

// インターフェース
#include "../../engine/lib/include/EngineCore/EngineCore.hpp"
#include "../../engine/lib/include/IWindow.hpp"
#include "../../engine/lib/include/IDevice.hpp"
#include "../../engine/lib/include/IFactory.hpp"
#include "../../engine/lib/include/ICommandList.hpp"
#include "../../engine/lib/include/ICommandQueue.hpp"
#include "../../engine/lib/include/ISwapChain.hpp"

#include "../../engine/lib/include/ViewPort.hpp"
#include "../../engine/lib/include/ScissorRect.hpp"

// ↓隠ぺいしたい
#include "../../engine/lib/src/Dx12/DepthStencil/DepthStencil.hpp"

#include "../../engine/lib/src/Dx12/RootSignature/RootSignature.hpp"
#include "../../engine/lib/src/Dx12/PipelineState/InputLayout.hpp"

#include "../../engine/lib/src/Dx12/Shader/VertexShader.hpp"
#include "../../engine/lib/src/Dx12/Shader/PixelShader.hpp"
#include "../../engine/lib/src/Dx12/PipelineState/PipelineState.hpp"

#include "../../engine/include/Camera/Camera2D.hpp"
#include "../../engine/include/Camera/Camera3D.hpp"

#include "../../engine/include/Buffer/VertexBuffer.hpp"
#include "../../engine/include/Buffer/IndexBuffer.hpp"
#include "../../engine/include/Buffer/ConstantBuffer.hpp"

#include "../../engine/include/Vertex/Vertex2D.hpp"
#include "../../engine/include/IndexData/IndexData.hpp"

#include "../../engine/include/Image/Image.hpp"

#include "../../engine/lib/src/Dx12/Buffer/Dx12Resource.hpp"

#include "../../engine/lib/src/Dx12/DescriptorHeap/DescriptorHeap.h"
#include "../../engine/lib/src/Dx12/Device/Device.hpp"

#include "../../engine/lib/src/Dx12/Texture/Dx12Texture.hpp"

#include <unordered_map>
#include <optional>

void gnMain() {
	using namespace engine;

	EngineCore::get()->init("windows", 640, 480);

	auto window = EngineWindow();
	auto device = EngineDevice();
	auto factory = EngineFactory();
	auto commandList = EngineCommandList();
	auto commandQueue = EngineCommandQueue();
	auto swapChain = EngineSwapChain();

	ViewPort viewPort{ .width = 640.0f, .height = 480.0f };
	ScissorRect scissorRect{ .right = 640, .bottom = 480 };

	auto depthStencil = createDepthStencil();
	if (depthStencil->init(window, device)) {
		OutputDebugString("DepthStencil Yes.\n");
	}

	RootSignatureDesc root{};
	root.setDescriptor(ParameterType::CBV, ShaderVisibility::Vertex, 0, 0);
	root.setDescriptor(ParameterType::CBV, ShaderVisibility::Vertex, 0, 1);
	root.setDescriptorTable(DescriptorRange::SRV, ShaderVisibility::Pixel, 1, 0, 0);
	auto rootSignature = RootSignature::create(device, root);

	InputLayout input{
		{ "POSITION", TextureFormat::R32G32B32_FLOAT },
		{ "TEXCOORD", TextureFormat::R32G32_FLOAT }
	};

	PipelineParameter pParameter{};
	pParameter.shaderParameter.vertex = {
		"TextureVertex", L"engine/lib/shader/TextureVertex.hlsl", "main", "vs_5_0"
	};
	pParameter.shaderParameter.pixel = {
		"TexturePixel", L"engine/lib/shader/TexturePixel.hlsl", "main", "ps_5_0"
	};
	pParameter.inputLayout = &input;
	pParameter.rootSignature = &rootSignature;
	pParameter.cullMode = CullMode::None;
	pParameter.fillMode = FillMode::Solid;
	pParameter.topologyType = TopologyType::Triangle;
	std::shared_ptr<core::Pipeline> pipeline{ new PipelineState{} };
	if (pipeline->init(device, pParameter)) {
		OutputDebugString("Pipeline Yes.\n");
	}

	// constant
	Camera3D cam{};

	struct CamMat {
		Matrix4x4 view;
		Matrix4x4 proj;
	} camMat{};

	camMat.view = cam.getView();
	camMat.proj = cam.getProjection();

	ConstantBuffer cameraUploader{};
	cameraUploader.init(device, &camMat, sizeof(CamMat));

	struct World {
		Matrix4x4 world;
	} world{};

	ConstantBuffer posUploader{};
	posUploader.init(device, &world, sizeof(World));

	std::vector<Vertex2DTexture> vertexes{
		{ { -0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f } },
		{ { -0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f } },
		{ {  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f } },
		{ {  0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f } },
	};
	VertexBuffer vertexBuffer{};
	vertexBuffer.init(device, vertexes.data(), sizeof(Vertex2DTexture), vertexes.size());

	IndexData indexData{};
	indexData.setTriangle(0, 1, 2);
	indexData.setTriangle(0, 2, 3);

	IndexBuffer indexBuffer{};
	indexBuffer.init(device, indexData.getData(), indexData.getStride(), indexData.getSize());

	Image img{ 32, 32 };
	for (size_t y = 0; y < 32; ++y) {
		for (size_t x = 0; x < img.getRowPitch(); x += img.getStride()) {
			img.setPixel(x, y, ColorI{ 0, 0, 255, 255 });
		}
	}

	Dx12Texture tex{};
	tex.load(device, img);

	while (EngineCore::get()->getWindow()->update()) {
		{
			commandList->reset();

			ColorF backColor{ 1.0f, 0.3f, 1.0f, 1.0f };

			// レンダーターゲットをセット
			commandList->resourceBarrier(swapChain, ResouceStates::Present, ResouceStates::RenderTarget);

			// ビューポート設定
			commandList->setViewport(viewPort);

			// シザー矩形の設定
			commandList->setScissorRect(scissorRect);

			// レンダーターゲットのクリア
			commandList->clearRenderTargetView(swapChain, backColor);

			// レンダーターゲットのクリア
			commandList->setRenderTargets(swapChain, depthStencil);

			// デプスステンシルのクリア
			commandList->clearDepthStencilView(depthStencil);
		}


		commandList->setRootSignature(rootSignature);
		commandList->setPipelineState(pipeline);

		// constant
		commandList->setConstantBuffer(cameraUploader, 0);

		world.world = gnLib::Matrix4x4::identity();
		static float f = 0.0f;
		f += 0.05f;
		posUploader.update(&world, sizeof(World));
		commandList->setConstantBuffer(posUploader, 1);

		commandList->setTexture(&tex, 2);

		commandList->setPrimitiveTopology();
		commandList->setVertexBuffer(vertexBuffer);
		commandList->setIndexBuffer(indexBuffer);


		// 画面の入れ替え
		{
			commandList->resourceBarrier(swapChain, ResouceStates::RenderTarget, ResouceStates::Present);

			commandList->close();
			commandQueue->executeCommand(commandList);

			swapChain->present();

			commandQueue->waitForPrevousFrame();
		}
	}
}
*/