/*
#include "../../engine/include/EngineMain/EngineMain.hpp"

#include "../../engine/lib/include/EngineCore/EngineCore.hpp"
#include "../../engine/lib/include/IWindow.hpp"
#include "../../engine/lib/include/IDevice.hpp"
#include "../../engine/lib/include/IFactory.hpp"
#include "../../engine/lib/include/ICommandList.hpp"
#include "../../engine/lib/include/ICommandQueue.hpp"
#include "../../engine/lib/include/ISwapChain.hpp"

#include "../../engine/lib/include/ViewPort.hpp"
#include "../../engine/lib/include/ScissorRect.hpp"

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

	/*
	// ���\�[�X�f�[�^
	// ��������

	ResourceDesc tdesc{};
	tdesc.width = 32;
	tdesc.height = 32;
	tdesc.depthOrArraySize = 1;
	tdesc.mipLevels = 1;
	tdesc.format = TextureFormat::R8G8B8A8_UNORM;
	tdesc.dimension = ResourceDimension::Texture2D;

	resource_ptr texResource = resource_ptr{ new Dx12Resource{} };
	if (!texResource->init(device, ResourceType::ShaderResource, tdesc, ResouceStates::PixelShaderResouce)) {
		return;
	}

	//auto* data = texResource->map();
	{
		texResource->writeToSubResource(
			img.getData(), img.getWidth(), img.getHeight(), img.getRowPitch(), img.getSlicePitch()
		);
	}
	//texResource->unMap();

	// �ŃX�N���v���q�[�v���
	DescriptorHeap heap{};
	if (!heap.init(device, 1, DescriptorType::CSV_SRV_UAV, DescriptorFlag::Visibe)) {
		return;
	}

	auto r = texResource.get();
	auto dx = static_cast<Dx12Resource*>(r);

	D3D12_SHADER_RESOURCE_VIEW_DESC view{};
	view.Format = dx->get()->GetDesc().Format;
	view.Texture2D.MipLevels = dx->get()->GetDesc().MipLevels;
	view.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	view.Texture2D.MostDetailedMip = 0;
	view.Texture2D.PlaneSlice = 0;
	view.Texture2D.ResourceMinLODClamp = 0.0f;
	view.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

	auto* dev = static_cast<Dx12Device*>(device.get());

	auto handle = heap.getCpuHandle();
	dev->get()->CreateShaderResourceView(dx->get(), &view, handle);
	// �����܂�
	

	Dx12Texture tex{};
	tex.load(device, img);

	while (EngineCore::get()->getWindow()->update()) {
		commandList->reset();

		ColorF backColor{ 1.0f, 0.3f, 1.0f, 1.0f };

		// �����_�[�^�[�Q�b�g���Z�b�g
		commandList->resourceBarrier(swapChain, ResouceStates::Present, ResouceStates::RenderTarget);

		// �r���[�|�[�g�ݒ�
		commandList->setViewport(viewPort);

		// �V�U�[��`�̐ݒ�
		commandList->setScissorRect(scissorRect);

		// �����_�[�^�[�Q�b�g�̃N���A
		commandList->clearRenderTargetView(swapChain, backColor);

		// �����_�[�^�[�Q�b�g�̃N���A
		commandList->setRenderTargets(swapChain, depthStencil);

		// �f�v�X�X�e���V���̃N���A
		commandList->clearDepthStencilView(depthStencil);


		commandList->setRootSignature(rootSignature);
		commandList->setPipelineState(pipeline);

		// constant
		commandList->setConstantBuffer(cameraUploader, 0);

		world.world = gnLib::Matrix4x4::identity();
		static float f = 0.0f;
		f += 0.05f;
		//world.world = Matrix4x4::rotationY(f);
		// world.world = world.world * Matrix4x4::rotationY(f);
		posUploader.update(&world, sizeof(World));
		commandList->setConstantBuffer(posUploader, 1);

		/*
		ID3D12DescriptorHeap* heaps[]{ tex.getHeap() };
		auto gpuHandle = tex.getHeap()->GetGPUDescriptorHandleForHeapStart();
		commandList->setDescriptorHeaps(_countof(heaps), heaps);
		commandList->setGraphicsRootDescriptorTable(2, gpuHandle);
		

		commandList->setTexture(&tex, 2);

		commandList->setPrimitiveTopology();
		commandList->setVertexBuffer(vertexBuffer);
		commandList->setIndexBuffer(indexBuffer);


		// ��ʂ̓���ւ�
		commandList->resourceBarrier(swapChain, ResouceStates::RenderTarget, ResouceStates::Present);

		commandList->close();
		commandQueue->executeCommand(commandList);

		swapChain->present();

		commandQueue->waitForPrevousFrame();
	}
}
*/