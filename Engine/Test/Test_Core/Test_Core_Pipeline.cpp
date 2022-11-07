/*
#include "../../engine/include/EngineMain/EngineMain.hpp"

// こちらは実装クラス
#include "../../engine/lib/src/Windows/Window.hpp"
#include "../../engine/lib/src/Dx12/include/Device/Device.hpp"
#include "../../engine/lib/src/Dx12/include/Device/Factory.hpp"
#include "../../engine/lib/src/Dx12/include/CommandList/Dx12CommandList.hpp"
#include "../../engine/lib/src/Dx12/include/CommandList/Dx12CommandQueue.hpp"
#include "../../engine/lib/src/Dx12/include/RenderTarget/RenderTarget.hpp"
#include "../../engine/lib/src/Dx12/include/SwapChain/Dx12SwapChain.hpp"
#include "../../engine/lib/src/Dx12/include/DepthStencil/DepthStencil.hpp"
#include "../../engine/lib/src/Dx12/include/RootSignature/RootSignature.hpp"
#include "../../engine/lib/src/Dx12/include/PipelineState/InputLayout.hpp"

#include "../../engine/include/Asset/AssetPath.hpp"
#include "../../engine/lib/src/Dx12/include/Shader/VertexShader.hpp"
#include "../../engine/lib/src/Dx12/include/Shader/PixelShader.hpp"
#include "../../engine/lib/src/Dx12/include/PipelineState/PipelineState.hpp"

#include "../../engine/include/Camera/Camera2D.hpp"

#include "../../engine/lib/src/Dx12/include/Buffer/ConstantBuffer.hpp"

#include "../../engine/include/Buffer/VertexBuffer.hpp"
#include "../../engine/include/Buffer/IndexBuffer.hpp"

#include "../../engine/include/Vertex/Vertex2D.hpp"
#include "../../engine/include/IndexData/IndexData.hpp"

#include "../../engine/include/Color/Color.hpp"

struct AP {
	static inline const std::wstring Path = L"Test/shader/";
};

void gnMain() {
	using namespace engine;

	std::shared_ptr<core::IWindow> window{ new Window{} };
	if (window->init("test", 640, 480)) {
		OutputDebugString("Window Yes.\n");
	}

	std::shared_ptr<core::IFactory> factory{ new Dx12Factory{} };
	if (factory->init()) {
		OutputDebugString("Factory Yes.\n");
	}

	std::shared_ptr<core::IDevice> device{ new Dx12Device{} };
	if (device->init(factory)) {
		OutputDebugString("Device Yes.\n");
	}

	std::shared_ptr<core::ICommandList> commandList{ new Dx12CommandList{} };
	if (commandList->init(device)) {
		OutputDebugString("CommandList Yes.\n");
	}

	std::shared_ptr<core::ICommandQueue> commandQueue{ new Dx12CommandQueue{} };
	if (commandQueue->init(device, commandList)) {
		OutputDebugString("CommandQueue Yes.\n");
	}

	ViewPort vp{ .width = 640.0f, .height = 480.0f };
	ScissorRect sr{ .right = 640, .bottom = 480 };

	std::shared_ptr<core::ISwapChain> swapChain{ new Dx12SwapChain{} };
	if (swapChain->init(window, factory, device, commandQueue)) {
		OutputDebugString("SwapChain Yes.\n");
	}

	ColorF backColor{ 1.0f, 0.3f, 1.0f, 1.0f };

	std::shared_ptr<core::DepthStencil> depthStencil{ new Dx12DepthStencil{} };
	if (depthStencil->init(window, device)) {
		OutputDebugString("DepthStencil Yes.\n");
	}

	// ルートシグネチャー
	D3D12_ROOT_PARAMETER param[2]{};
	// 定数バッファ
	param[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	param[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	param[0].Descriptor.RegisterSpace = 0;   // space0
	param[0].Descriptor.ShaderRegister = 0;  // b0

	// WorldMatrix用のバッファ
	param[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	param[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	param[1].Descriptor.RegisterSpace = 0;   // space0
	param[1].Descriptor.ShaderRegister = 1;  // b1

	D3D12_ROOT_SIGNATURE_DESC desc{};
	desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	desc.NumParameters = _countof(param);
	desc.pParameters = param;
	auto rootSignature = RootSignature::create(device, desc);

	VertexShader vertexShader{ AssetPath<AP>(L"TestVertex.hlsl"), "main", "vs_5_0" };

	// ピクセル
	PixelShader pixelShader{ AssetPath<AP>(L"TestPixel.hlsl"), "main", "ps_5_0" };

	InputLayout input {
		{ "POSITION", TextureFormat::R32G32B32_FLOAT },
		{ "COLOR", TextureFormat::R32G32B32A32_FLOAT }
	};

	PipelineParameter pParameter{};
	pParameter.pipelineShader.vertexShader = vertexShader.getByteCode();
	pParameter.pipelineShader.pixelShader = pixelShader.getByteCode();
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
	Camera2D cam{};
	
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

	std::vector<Vertex2DColor> vertexes{
		{ { -50, -50, 0.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
		{ { -50,  50, 0.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
		{ {  50,  50, 0.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } },
		{ {  50, -50, 0.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } }
	};
	VertexBuffer vertexBuffer{};
	vertexBuffer.init(device, vertexes.data(), sizeof(Vertex2DColor), vertexes.size());

	IndexData indexData{};
	indexData.setTriangle(0, 1, 2);
	indexData.setTriangle(0, 2, 3);
	IndexBuffer indexBuffer{};
	indexBuffer.init(device, indexData.getData(), indexData.getStride(), indexData.getSize());

	while (window->update()) {
		{
			commandList->reset();

			// レンダーターゲットをセット
			commandList->resourceBarrier(swapChain, ResouceStates::Present, ResouceStates::RenderTarget);

			// ビューポート設定
			commandList->setViewport(vp);

			// シザー矩形の設定
			commandList->setScissorRect(sr);

			// レンダーターゲットのクリア
			commandList->clearRenderTargetView(swapChain, backColor);

			// レンダーターゲットのクリア
			commandList->setRenderTargets(swapChain, depthStencil);

			// デプスステンシルのクリア
			commandList->clearDepthStencilView(depthStencil);
		}

		{
			commandList->setRootSignature(rootSignature);
			commandList->setPipelineState(pipeline);

			// constant
			commandList->setConstantBuffer(cameraUploader, 0);

			world.world = gnLib::Matrix4x4::identity();
			posUploader.update(&world, sizeof(World));
			commandList->setConstantBuffer(posUploader, 1);

			commandList->setPrimitiveTopology();
			commandList->setVertexBuffer(vertexBuffer);
			commandList->setIndexBuffer(indexBuffer);
		}

		{

			// 画面の入れ替え
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