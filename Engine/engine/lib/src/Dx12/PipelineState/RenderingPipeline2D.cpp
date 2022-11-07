#include "RenderingPipeline2D.hpp"
#include "../CommandList/Dx12CommandList.hpp"
#include "../RootSignature/RootSignature.hpp"
#include "../PipelineState/PipelineState.hpp"
#include "../PipelineState/InputLayout.hpp"
#include "../Shader/VertexShader.hpp"
#include "../Shader/PixelShader.hpp"
#include "../../../engine/include/Asset/AssetPath.hpp"

namespace engine {

	namespace {
		struct TestShaderPath {
			static inline const std::wstring Path = L"Test/shader/";
		};
	}

	RenderingPipeline2D::RenderingPipeline2D()
		: rootSignatureList()
		, pipelineStateList()
	{
	}

	RenderingPipeline2D::~RenderingPipeline2D()
	{
	}

	void RenderingPipeline2D::init()
	{
		createColorPipeline();

		createTexturePipeline();
	}

	void RenderingPipeline2D::setPipeline(RenderState _state)
	{
		//size_t index = static_cast<size_t>(_state);
		//EngineCommand()->get()->SetGraphicsRootSignature(rootSignatureList[index].get());
		//EngineCommand()->get()->SetPipelineState(pipelineStateList[index].get());
	}

	void RenderingPipeline2D::createColorPipeline()
	{
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
		//auto rootSignature = RootSignature::create(desc);

		/*
		// パイプラインステート
		// 頂点
		VertexShader vertexShader{ AssetPath<TestShaderPath>(L"TestVertex.hlsl"), "main", "vs_5_0" };

		// ピクセル
		PixelShader pixelShader{ AssetPath<TestShaderPath>(L"TestPixel.hlsl"), "main", "ps_5_0" };

		auto input = InputLayout{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		};
		*/

		PipelineParameter parameter{};
		// parameter.pipelineShader.vertexShader = vertexShader.getByteCode();
		// parameter.pipelineShader.pixelShader = pixelShader.getByteCode();
		// parameter.inputLayout = &input;
		// parameter.rootSignature = &rootSignature;
		// parameter.cullMode = CullMode::None;
		// parameter.fillMode = FillMode::Solid;
		// parameter.topologyType = TopologyType::Triangle;


		//auto pipeliseState = PipelineState::create(parameter);

		///rootSignatureList.emplace_back(rootSignature);
		//pipelineStateList.emplace_back(pipeliseState);
	}

	void RenderingPipeline2D::createTexturePipeline()
	{
		D3D12_DESCRIPTOR_RANGE range[1];
		range[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		range[0].NumDescriptors = -1;     // -1 or UINT_MAX を指定
		range[0].BaseShaderRegister = 0;  // 0
		range[0].RegisterSpace = 0;       // space0
		range[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		const size_t PARAMETER_SIZE = 3;
		
		D3D12_ROOT_PARAMETER param[PARAMETER_SIZE]{};

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

		// SRV
		param[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		param[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
		param[2].DescriptorTable.NumDescriptorRanges = 1;  // D3D12_DESCRIPTOR_HEAP_DESCのNumDescriptorsと同じにする
		param[2].DescriptorTable.pDescriptorRanges = &range[0];

		// サンプラー
		D3D12_STATIC_SAMPLER_DESC sampler[1]{};
		sampler[0].Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
		sampler[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		sampler[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		sampler[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		sampler[0].MinLOD = -FLT_MAX;
		sampler[0].MaxLOD = FLT_MAX;
		sampler[0].MaxAnisotropy = 0;
		sampler[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		sampler[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

		D3D12_ROOT_SIGNATURE_DESC desc{};
		desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		desc.NumParameters = _countof(param);
		desc.pParameters = param;
		desc.NumStaticSamplers = _countof(sampler);
		desc.pStaticSamplers = sampler;

		//auto rootSignature = RootSignature::create(desc);

		/*
		// 頂点
		VertexShader vertexShader{ AssetPath<ShaderPath>(L"TextureVertex.hlsl"), "main", "vs_5_0" };

		// ピクセル
		PixelShader pixelShader{ AssetPath<ShaderPath>(L"TexturePixel.hlsl"), "main", "ps_5_0" };

		auto input = InputLayout{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		};
		*/

		PipelineParameter pParameter{};
		// pParameter.pipelineShader.vertexShader = vertexShader.getByteCode();
		// pParameter.pipelineShader.pixelShader = pixelShader.getByteCode();
		// pParameter.inputLayout = &input;
		// pParameter.rootSignature = &rootSignature;
		// pParameter.cullMode = CullMode::None;
		// pParameter.fillMode = FillMode::Solid;
		// pParameter.topologyType = TopologyType::Triangle;
		//auto pipeliseState = PipelineState::create(pParameter);

		//rootSignatureList.emplace_back(rootSignature);
		//pipelineStateList.emplace_back(pipeliseState);
	}

}