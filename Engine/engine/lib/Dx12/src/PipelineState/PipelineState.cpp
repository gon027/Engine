#include <include/PipelineState/PipelineState.hpp>
#include "../../include/Library/d3dx12.h"
#include <include/EngineCore/EngineCore.hpp>
#include <include/Device/Device.hpp>
#include <include/PipelineState/InputLayout.hpp>
#include <include/RootSignature/RootSignature.hpp>

namespace engine {

	PipelineState PipelineState::create(const PipelineParameter& _pipelineParameter)
	{
		PipelineState result{};
		result.init(_pipelineParameter);

		return result;
	}

	PipelineState::PipelineState()
		: pipelineState(nullptr)
	{
	}

	PipelineState::~PipelineState()
	{
	}

	bool PipelineState::init(const PipelineParameter& _pipelineParameter)
	{
		D3D12_GRAPHICS_PIPELINE_STATE_DESC desc{};

		desc.InputLayout = _pipelineParameter.inputLayout->getInputLayout();

		desc.pRootSignature = _pipelineParameter.rootSignature->get();

		desc.VS = _pipelineParameter.pipelineShader.vertexShader;
		desc.HS = _pipelineParameter.pipelineShader.hallShader;
		desc.DS = _pipelineParameter.pipelineShader.domainShader;
		desc.GS = _pipelineParameter.pipelineShader.geometryShader;
		desc.PS = _pipelineParameter.pipelineShader.pixelShader;
		
		desc.RasterizerState = CD3DX12_RASTERIZER_DESC{ D3D12_DEFAULT };
		desc.RasterizerState.CullMode = static_cast<D3D12_CULL_MODE>(_pipelineParameter.cullMode);
		desc.RasterizerState.FillMode = static_cast<D3D12_FILL_MODE>(_pipelineParameter.fillMode);

		desc.BlendState = CD3DX12_BLEND_DESC{ D3D12_DEFAULT };
		desc.BlendState.IndependentBlendEnable = FALSE;
		for (size_t i{ 0 }; i < _countof(desc.BlendState.RenderTarget); ++i) {
			auto& rt = desc.BlendState.RenderTarget[i];
			rt.BlendEnable    = _pipelineParameter.isBlendEnable;  // ブレンディングを有効
			rt.LogicOpEnable  = FALSE; // 論理演算を無効にする
			rt.SrcBlend              = D3D12_BLEND_SRC_ALPHA;
			rt.DestBlend             = D3D12_BLEND_INV_SRC_ALPHA;
			rt.BlendOp               = D3D12_BLEND_OP_ADD;
			rt.SrcBlendAlpha         = D3D12_BLEND_SRC_ALPHA;
			rt.DestBlendAlpha        = D3D12_BLEND_INV_SRC_ALPHA;
			rt.BlendOpAlpha          = D3D12_BLEND_OP_ADD;
			rt.LogicOp               = D3D12_LOGIC_OP_NOOP;
			rt.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
		}

		desc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC{ D3D12_DEFAULT };
		desc.DepthStencilState.DepthEnable = _pipelineParameter.isDepthEnable;
		desc.DepthStencilState.StencilEnable = _pipelineParameter.isStencilEnable;
		desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;

		desc.PrimitiveTopologyType = static_cast<D3D12_PRIMITIVE_TOPOLOGY_TYPE>(_pipelineParameter.topologyType);
		desc.DSVFormat        = DXGI_FORMAT_D32_FLOAT;
		desc.SampleMask       = D3D12_DEFAULT_SAMPLE_MASK;
		desc.NumRenderTargets = 1;
		desc.RTVFormats[0]    = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;

		auto hr = EngineDevice()->get()->CreateGraphicsPipelineState(
			&desc,
			IID_PPV_ARGS(pipelineState.GetAddressOf())
		);

		if (FAILED(hr)) {
			return false;
		}


		return true;
	}

}