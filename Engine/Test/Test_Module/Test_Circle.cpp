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
#include "../../engine/include/Transform/Transform.hpp"

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

using namespace engine;

const static std::vector<int> Indexes{

};

struct Particle {
	static constexpr float Radius = 10.0f;
	static constexpr float Tau = gnLib::pi * 2;
	const size_t Num = 25;
	const float theta = Tau / static_cast<float>(Num);

	Particle()
		: vertexes()
		, vertexBuffer()
		, indexBuffer() 
		, posUploader()
		, x(0.0f), y(0.0f), z(0.0f)
	{}

	void init(device_ptr _device) {
		vertexes.resize(Num);
		for (int i = 0; i < Num; ++i) {
			float x{ Radius * cosf(static_cast<float>(theta * i)) };
			float y{ Radius * sinf(static_cast<float>(theta * i)) };
			vertexes[i] = { { x, y, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
		}
		vertexBuffer.init(_device, vertexes.data(), sizeof(V), vertexes.size());

		IndexData indexData{};
		for (int i = 1; i < Num - 1; ++i) {
			indexData.setTriangle(0, i, i + 1);
		}
		indexBuffer.init(_device, indexData.getData(), indexData.getStride(), indexData.getSize());

		posUploader.init(_device, &world, sizeof(World));
	}

	float xSpeed = 1.0f;
	float ySpeed = 2.0f;

	void update() {
		x += xSpeed;
		y += ySpeed;

		if (y + Radius >= 240.0f || y - Radius <= -240.0f) {
			ySpeed = -ySpeed;
		}

		if (x + Radius >= 320.0f || x - Radius <= -320.0f) {
			xSpeed = -xSpeed;
		}

		world.world = gnLib::Matrix4x4::translation(x, y, z);
	}

	void draw(commandList_ptr _commandList) {
		posUploader.update(&world, sizeof(World));
		_commandList->setConstantBuffer(posUploader, 1);

		_commandList->setPrimitiveTopology();
		_commandList->setVertexBuffer(vertexBuffer);
		_commandList->setIndexBuffer(indexBuffer);
	}

	void setPos(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
		world.world = gnLib::Matrix4x4::translation(x, y, z);
	}

	struct V {
		Vec3 position;
		Vec4 color;
	};
	std::vector<V> vertexes;

	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;

	struct World {
		Matrix4x4 world;
	} world{};

	ConstantBuffer posUploader;

	float x, y, z;
};

void gnMain() {
	EngineCore::get()->init("test", 640, 480);
	auto window = EngineWindow();
	auto device = EngineDevice();
	auto commandList = EngineCommandList();
	auto commandQueue = EngineCommandQueue();
	auto swapChain = EngineSwapChain();
	auto depthStencil = EngineDepthStencil();

	const ViewPort vp{ .width = 640.0f, .height = 480.0f };
	const ScissorRect sr{ .right = 640, .bottom = 480 };
	const ColorF backColor{ 0.0f, 0.7f, 0.7f, 1.0f };

	RootSignatureDesc root{};
	root.setDescriptor(ParameterType::CBV, ShaderVisibility::Vertex, 0, 0);
	root.setDescriptor(ParameterType::CBV, ShaderVisibility::Vertex, 0, 1);
	auto rootSignature = RootSignature::create(device, root);

	InputLayout input{
		{ "POSITION", TextureFormat::R32G32B32_FLOAT },
		{ "COLOR", TextureFormat::R32G32B32A32_FLOAT }
	};

	PipelineParameter pParameter{};
	pParameter.shaderParameter.vertex = {
		"TextureVertex", L"Test/shader/TestVertex.hlsl", "main", "vs_5_0"
	};
	pParameter.shaderParameter.pixel = {
		"TexturePixel", L"Test/shader/TestPixel.hlsl", "main", "ps_5_0"
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
	Camera2D cam{};

	struct CamMat {
		Matrix4x4 view;
		Matrix4x4 proj;
	} camMat{};

	camMat.view = cam.getView();
	camMat.proj = cam.getProjection();

	ConstantBuffer cameraUploader{};
	cameraUploader.init(device, &camMat, sizeof(CamMat));

	// Particle 
	const size_t MaxNum = 10;
	std::vector<Particle> particles(MaxNum);
	for (size_t i = 0; i < MaxNum; ++i) {
		particles[i].init(device);
	}

	float x = 0.0f;
	for (size_t i = 0; i < MaxNum; ++i) {
		particles[i].setPos(15.0f * i, 0.0f, 0.0);
	}

	while (window->update()) {
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


		commandList->setRootSignature(rootSignature);
		commandList->setPipelineState(pipeline);

		// constant
		commandList->setConstantBuffer(cameraUploader, 0);

		for (size_t i = 0; i < MaxNum; ++i) {
			particles[i].update();
		}
		
		for (size_t i = 0; i < MaxNum; ++i) {
			particles[i].draw(commandList);
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