#include "ModelPipeline.h"

#include "../../lib/src/Dx12/PipelineState/InputLayout.hpp"

namespace engine {

	ModelPipeline::ModelPipeline(device_ptr _device)
		: rootSignature()
		, pipelineState(new PipelineState{})
	{
		RootSignatureDesc root{};
		root.setDescriptor(ParameterType::CBV, ShaderVisibility::Vertex, 0, 0);
		root.setDescriptor(ParameterType::CBV, ShaderVisibility::Vertex, 0, 1);
		root.setDescriptor(ParameterType::CBV, ShaderVisibility::All, 0, 2);
		root.setDescriptorTable(DescriptorRange::SRV, ShaderVisibility::Pixel, 1, 0, 0);
		// root.setDescriptorTable(DescriptorRange::SRV, ShaderVisibility::Pixel, 1, 0, 1);
		rootSignature = RootSignature::create(_device, root);

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
		if (pipelineState->init(_device, pParameter)) {
			OutputDebugString("Pipeline Succses.\n");
		}
	}

}