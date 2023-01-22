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

// ImGui
#include "../../engine/lib/imgui/imgui.h"
//#include "../../engine/lib/imgui/imgui_impl_win32.h"
//#include "../../engine/lib/imgui/imgui_impl_dx12.h"

using namespace engine;

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

	
	auto dev = (Dx12Device*)(device.get());
	assert(dev != nullptr);

	D3D12DescriptorHeap srvDescHeap{ nullptr };
	{
		D3D12_DESCRIPTOR_HEAP_DESC desc{};
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		desc.NodeMask = 0;
		desc.NumDescriptors = 1;
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

		
		dev->get()->CreateDescriptorHeap(
			&desc, IID_PPV_ARGS(srvDescHeap.ReleaseAndGetAddressOf())
		);
	}

	//IMGUI_CHECKVERSION();

	
	ImGui::CreateContext();

	/*
	ImGui_ImplWin32_Init(window->getHandle());
	ImGui_ImplDX12_Init(
		dev->get(), 2, DXGI_FORMAT_R8G8B8A8_UNORM, srvDescHeap.Get(),
		srvDescHeap->GetCPUDescriptorHandleForHeapStart(),
		srvDescHeap->GetGPUDescriptorHandleForHeapStart()
	);

	/*
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

		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("AAAAAAAA");
		ImGui::SetWindowSize(
			ImVec2(200, 200), ImGuiCond_::ImGuiCond_FirstUseEver
		);
		ImGui::End();

		ImGui::Render();
		commandList->setDescriptorHeaps(1, srvDescHeap.GetAddressOf());

		auto cmd = (Dx12CommandList*)commandList.get();


		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), cmd->get());

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

	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	*/
}