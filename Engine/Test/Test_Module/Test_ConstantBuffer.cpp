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
	if (!InKey.init()) return;

	Time time{};

	const size_t FIXED_FPS = 30;
	const float MIN_FRAME_TIME = 1.0f / static_cast<float>(FIXED_FPS);

	float fps = 0.0f;

	const ViewPort vp{ .width = 640.0f, .height = 480.0f };
	const ScissorRect sr{ .right = 640, .bottom = 480 };
	const ColorF backColor{ 0.0f, 0.7f, 0.7f, 1.0f };

	RootSignatureDesc root{};
	root.setDescriptor(ParameterType::CBV, ShaderVisibility::Vertex, 0, 0);
	root.setDescriptor(ParameterType::CBV, ShaderVisibility::Vertex, 0, 1);
	root.setDescriptor(ParameterType::CBV, ShaderVisibility::All, 0, 2);
	root.setDescriptorTable(DescriptorRange::SRV, ShaderVisibility::Pixel, 1, 0, 0);
	auto rootSignature = RootSignature::create(device, root);

	InputLayout input{
		{ "POSITION", TextureFormat::R32G32B32_FLOAT },
		{ "NORMAL",   TextureFormat::R32G32B32_FLOAT },
		{ "TEXCOORD", TextureFormat::R32G32_FLOAT }
	};

	PipelineParameter pParameter{};
	pParameter.shaderParameter.vertex = {
		"TextureVertex", L"Test/shader/TestVertex3D.hlsl", "main", "vs_5_0"
	};
	pParameter.shaderParameter.pixel = {
		"TexturePixel", L"Test/shader/TestPixel3D.hlsl", "main", "ps_5_0"
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

	struct Value{
		float value;
	};

	Value v{ 0.0f };

	// ConstantBuffer cb{};
	// cb.init(device, &v, sizeof(v));

	std::vector<ConstantBuffer> vcb{};
	vcb.resize(100);

	while (window->update()) {
		Sleep(1);
	}

}
*/