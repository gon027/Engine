#pragma once

#include <optional>
#include <unordered_map>
#include "../Library/Librarys.hpp"
#include "../../../include/Pipeline.hpp"

namespace engine {

	class InputLayout;
	class RootSignature;

	struct ShaderInfo {
		std::string name;
		std::wstring fileName;
		std::string entryPoint;
		std::string target;
	};

	struct ShaderParameter {
		std::optional<ShaderInfo> vertex;
		std::optional<ShaderInfo> hull;
		std::optional<ShaderInfo> domain;
		std::optional<ShaderInfo> geometry;
		std::optional<ShaderInfo> pixel;
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
		ShaderParameter shaderParameter;
		CullMode cullMode;
		TopologyType topologyType;
		FillMode fillMode;
		bool isDepthEnable = true;
		bool isStencilEnable = true;
		bool isBlendEnable = true;
	};

	class PipelineState : public core::Pipeline {
	public:
		static PipelineState create(device_ptr _device, const PipelineParameter& _pipelineParameter);

	public:
		PipelineState();
		~PipelineState();

		bool init(device_ptr _device, const PipelineParameter& _pipelineParameter) override;

		inline ID3D12PipelineState* const get() const {
			return pipelineState.Get();
		}

	private:
		D3D12PipelineState pipelineState;
	};

}