#pragma once

#include <memory>
#include "../Library/Librarys.hpp"
#include "../../../include/Fwd.hpp"
#include "../../../../../engine/include/Type/Type.hpp"

namespace engine {

	enum class ParameterType {
		CBV, SRV, UAV
	};

	enum class ShaderVisibility {
		All,
		Vertex,
		Hull,
		Domain,
		Geometry,
		Pixel,
		Amplification,
		Mesh,
	};

	enum class DescriptorRange {
		CBV, SRV, UAV, SAMPLER
	};

	struct DescriptorParameter {
		ParameterType parameterType;
		ShaderVisibility shaderVisibility;
		u32 registerSpace;
		u32 shaderRegister;
	};

	struct DescriptorTableParameter {
		DescriptorRange desciropterRange;
		ShaderVisibility shaderVisibility;
		u32 numDescriptorRanges;
		u32 registerSpace;
		u32 shaderRegister;
	};

	struct ConstansParameter {
		u32 shaderRegister;
		u32 registerSpace;
		u32 num32BitValues;
	};

	class RootSignatureDesc {
	public:
		RootSignatureDesc();
		~RootSignatureDesc() = default;

		void setDescriptor(ParameterType _param, ShaderVisibility _visibility, u32 _registerSpace, u32 _shaderRegister);

		void setDescriptorTable(
			DescriptorRange _range, ShaderVisibility _visibility, u32 _numDescriptorRanges, u32 _registerSpace, u32 _shaderRegister
		);

		void setConstants(u32 _shaderRegister, u32 _registerSpace, u32 _num32BitValues);

		DescriptorParameter& getDescriptor(u64 _index);

		DescriptorTableParameter& getDescriptorTable(u64 _index);

		ConstansParameter& getConstans(u64 _index);

		u64 getDescriptorSize() const;

		u64 getDescriptorTableSize() const;

		u64 getConstansSize() const;

	private:
		std::vector<DescriptorParameter> descriptorParamegers;
		std::vector<DescriptorTableParameter> descriptorTableParameters;
		std::vector<ConstansParameter> constansParameters;
	};

	class RootSignature {
	public:
		static RootSignature create(device_ptr _device, const D3D12_ROOT_SIGNATURE_DESC& _desc);

		static RootSignature create(device_ptr _device, RootSignatureDesc& _desc);

	public:
		RootSignature();
		~RootSignature();

		bool init(device_ptr _device, const D3D12_ROOT_SIGNATURE_DESC& _desc);

		bool init(device_ptr _device, RootSignatureDesc& _desc);

		inline ID3D12RootSignature* const get() const {
			return rootSignature.Get();
		}

	private:
		D3D12RootSignature rootSignature;
	};

}