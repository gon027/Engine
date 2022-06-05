#pragma once

#include <include/Library/Librarys.hpp>

namespace engine {

	class InputLayout;
	class RootSignature;

	struct PipelineShader {
		D3D12_SHADER_BYTECODE vertexShader{};
		D3D12_SHADER_BYTECODE hallShader{};
		D3D12_SHADER_BYTECODE domainShader{};
		D3D12_SHADER_BYTECODE geometryShader{};
		D3D12_SHADER_BYTECODE pixelShader{};
	};

	enum class TopologyType {
		Undefined = D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED,
		Point     = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT,
		Line      = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE,
		Triangle  = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,
		Patch     = D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH
	};

	enum class FillMode {
		WaireFrame  = D3D12_FILL_MODE_WIREFRAME,
		Solid       = D3D12_FILL_MODE_SOLID
	};

	enum class CullMode {
		None  = D3D12_CULL_MODE_NONE,
		Front = D3D12_CULL_MODE_FRONT,
		Back  = D3D12_CULL_MODE_BACK,
	};

	struct PipelineParameter {
		InputLayout* inputLayout;
		RootSignature* rootSignature;
		PipelineShader pipelineShader;
		CullMode cullMode;
		TopologyType topologyType;
		bool isDepthEnable = true;
		bool isStencilEnable = true;
		bool isBlendEnable = true;
	};

	class PipelineState {
	public:
		static PipelineState create(const PipelineParameter& _pipelineParameter);

	public:
		PipelineState();
		~PipelineState();

		bool init(const PipelineParameter& _pipelineParameter);

		inline ID3D12PipelineState* const get() const {
			return pipelineState.Get();
		}

	private:
		D3D12PipelineState pipelineState;
	};

}