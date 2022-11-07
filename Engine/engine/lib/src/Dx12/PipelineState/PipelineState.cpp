#include "PipelineState.hpp"
#include "../Library/d3dx12.h"
#include "../Device/Device.hpp"
#include "../PipelineState/InputLayout.hpp"
#include "../RootSignature/RootSignature.hpp"
#include "../Common/Helper.hpp"
#include "../Shader/VertexShader.hpp"
#include "../Shader/PixelShader.hpp"

#include "../../../include/EngineCore/Common.hpp"
#include "../Shader/Dx12Shader.hpp"
#include "../Shader/Dx12ShaderManager.hpp"

namespace engine {

	namespace {

		D3D12_INPUT_ELEMENT_DESC toInputElementDesc(const InputElement& _elem) {
			D3D12_INPUT_ELEMENT_DESC res{};
			res.SemanticName = _elem.semanticName.c_str();
			res.SemanticIndex = 0;
			res.Format = toFormat(_elem.format);  // 後で考える
			res.InputSlot = 0;
			res.AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
			res.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
			res.InstanceDataStepRate = 0;
			return res;
		}

	}

	PipelineState PipelineState::create(device_ptr _device, const PipelineParameter& _pipelineParameter)
	{
		PipelineState result{};
		result.init(_device, _pipelineParameter);

		return result;
	}

	PipelineState::PipelineState()
		: pipelineState(nullptr)
	{
	}

	PipelineState::~PipelineState()
	{
	}

	bool PipelineState::init(device_ptr _device, const PipelineParameter& _pipelineParameter)
	{
		assert(_device != nullptr);

		auto* device = static_cast<Dx12Device*>(_device.get());

		D3D12_GRAPHICS_PIPELINE_STATE_DESC desc{};

		std::vector<D3D12_INPUT_ELEMENT_DESC> elements{};
		for (size_t i = 0; i < _pipelineParameter.inputLayout->getSize(); ++i) {
			auto e = toInputElementDesc(_pipelineParameter.inputLayout->getElement(i));
			elements.emplace_back(e);
		}
		desc.InputLayout.NumElements = static_cast<UINT>(elements.size());
		desc.InputLayout.pInputElementDescs = elements.data();

		desc.pRootSignature = _pipelineParameter.rootSignature->get();
		
		if (_pipelineParameter.shaderParameter.vertex != std::nullopt) {
			ShaderInfo sInfo = _pipelineParameter.shaderParameter.vertex.value();
			desc.VS = Dx12ShaderManager::get()->addVertex(sInfo).getByteCode();
		}

		if (_pipelineParameter.shaderParameter.hull != std::nullopt) {

		}

		if (_pipelineParameter.shaderParameter.domain != std::nullopt) {

		}

		if (_pipelineParameter.shaderParameter.geometry != std::nullopt) {

		}

		if (_pipelineParameter.shaderParameter.pixel != std::nullopt) {
			ShaderInfo pInfo = _pipelineParameter.shaderParameter.pixel.value();
			desc.PS = Dx12ShaderManager::get()->addPixel(pInfo).getByteCode();
		}

		//desc.VS = _pipelineParameter.pipelineShader.vertexShader;
		// desc.HS = _pipelineParameter.pipelineShader.hallShader;
		// desc.DS = _pipelineParameter.pipelineShader.domainShader;
		// desc.GS = _pipelineParameter.pipelineShader.geometryShader;
		// desc.PS = _pipelineParameter.pipelineShader.pixelShader;
		
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

		auto hr = device->get()->CreateGraphicsPipelineState(
			&desc,
			IID_PPV_ARGS(pipelineState.GetAddressOf())
		);

		if (FAILED(hr)) {
			return false;
		}


		return true;
	}

}