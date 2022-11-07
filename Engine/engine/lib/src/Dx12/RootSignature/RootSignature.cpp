#include "RootSignature.hpp"
#include "../Device/Device.hpp"
#include <unordered_map>

namespace engine {

	namespace {
	
		static const std::unordered_map<ParameterType, D3D12_ROOT_PARAMETER_TYPE> RootParameterTypeList{
			{ ParameterType::CBV, D3D12_ROOT_PARAMETER_TYPE_CBV },
			{ ParameterType::SRV, D3D12_ROOT_PARAMETER_TYPE_SRV },
			{ ParameterType::UAV, D3D12_ROOT_PARAMETER_TYPE_UAV }
		};
	
		static const std::unordered_map<ShaderVisibility, D3D12_SHADER_VISIBILITY> ShaderVisibilityList {
			{ ShaderVisibility::All,           D3D12_SHADER_VISIBILITY_ALL },
			{ ShaderVisibility::Vertex,        D3D12_SHADER_VISIBILITY_VERTEX },
			{ ShaderVisibility::Hull,          D3D12_SHADER_VISIBILITY_HULL },
			{ ShaderVisibility::Domain,        D3D12_SHADER_VISIBILITY_DOMAIN },
			{ ShaderVisibility::Geometry,      D3D12_SHADER_VISIBILITY_GEOMETRY },
			{ ShaderVisibility::Pixel,         D3D12_SHADER_VISIBILITY_PIXEL },
			{ ShaderVisibility::Amplification, D3D12_SHADER_VISIBILITY_AMPLIFICATION },
			{ ShaderVisibility::Mesh,          D3D12_SHADER_VISIBILITY_MESH },
		};
	
		static const std::unordered_map<DescriptorRange, D3D12_DESCRIPTOR_RANGE_TYPE> DescriptorRangeList {
			{ DescriptorRange::CBV,     D3D12_DESCRIPTOR_RANGE_TYPE_CBV },
			{ DescriptorRange::SRV    , D3D12_DESCRIPTOR_RANGE_TYPE_SRV },
			{ DescriptorRange::UAV    , D3D12_DESCRIPTOR_RANGE_TYPE_UAV },
			{ DescriptorRange::SAMPLER, D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER }
		};
	
	}

	RootSignatureDesc::RootSignatureDesc()
		: descriptorParamegers()
		, descriptorTableParameters()
		, constansParameters()
	{
	}

	void RootSignatureDesc::setDescriptor(ParameterType _param, ShaderVisibility _visibility, u32 _registerSpace, u32 _shaderRegister)
	{
		DescriptorParameter parameter{};
		parameter.parameterType = _param;
		parameter.shaderVisibility = _visibility;
		parameter.registerSpace = _registerSpace;
		parameter.shaderRegister = _shaderRegister;
		
		descriptorParamegers.emplace_back(parameter);
	}

	void RootSignatureDesc::setDescriptorTable(
		DescriptorRange _range, ShaderVisibility _visibility, u32 _numDescriptorRanges, u32 _registerSpace, u32 _shaderRegister
	)
	{
		DescriptorTableParameter parameter{};
		parameter.desciropterRange = _range;
		parameter.shaderVisibility = _visibility;
		parameter.numDescriptorRanges = _numDescriptorRanges;
		parameter.registerSpace = _registerSpace;
		parameter.shaderRegister = _shaderRegister;
		
		descriptorTableParameters.emplace_back(parameter);
	}

	void RootSignatureDesc::setConstants(u32 _shaderRegister, u32 _registerSpace, u32 _num32BitValues)
	{
		ConstansParameter parameter{};
		parameter.shaderRegister = _shaderRegister;
		parameter.registerSpace = _registerSpace;
		parameter.num32BitValues = _num32BitValues;
	}

	DescriptorParameter& RootSignatureDesc::getDescriptor(u64 _index)
	{
		return descriptorParamegers[_index];
	}

	DescriptorTableParameter& RootSignatureDesc::getDescriptorTable(u64 _index)
	{
		return descriptorTableParameters[_index];
	}

	ConstansParameter& RootSignatureDesc::getConstans(u64 _index)
	{
		return constansParameters[_index];
	}

	u64 RootSignatureDesc::getDescriptorSize() const
	{
		return descriptorParamegers.size();
	}

	u64 RootSignatureDesc::getDescriptorTableSize() const
	{
		return descriptorTableParameters.size();
	}

	u64 RootSignatureDesc::getConstansSize() const
	{
		return constansParameters.size();
	}

	RootSignature RootSignature::create(device_ptr _device, const D3D12_ROOT_SIGNATURE_DESC& _desc)
	{
		RootSignature result{};
		result.init(_device, _desc);

		return result;
	}

	RootSignature RootSignature::create(device_ptr _device, RootSignatureDesc& _desc)
	{
		RootSignature result{};
		result.init(_device, _desc);

		return result;
	}

	RootSignature::RootSignature()
		: rootSignature(nullptr)
	{
	}

	RootSignature::~RootSignature()
	{
	}

	bool RootSignature::init(device_ptr _device, const D3D12_ROOT_SIGNATURE_DESC& _desc)
	{
		assert(_device != nullptr);

		auto* device = static_cast<Dx12Device*>(_device.get());

		HRESULT hr{};

		D3DBlob signature{ nullptr }, error{ nullptr };
		hr = D3D12SerializeRootSignature(
			&_desc,
			D3D_ROOT_SIGNATURE_VERSION_1,
			signature.GetAddressOf(),
			error.GetAddressOf()
		);

		if (FAILED(hr) || error) {
			return false;
		}

		hr = device->get()->CreateRootSignature(
			0,
			signature->GetBufferPointer(),
			signature->GetBufferSize(),
			IID_PPV_ARGS(rootSignature.GetAddressOf())
		);

		if (FAILED(hr)) {
			return false;
		}

		return true;
	}

	bool RootSignature::init(device_ptr _device, RootSignatureDesc& _desc)
	{
		assert(_device != nullptr);

		auto* device = static_cast<Dx12Device*>(_device.get());

		const auto size = _desc.getDescriptorSize() + _desc.getDescriptorTableSize() + _desc.getConstansSize();
		std::vector<D3D12_ROOT_PARAMETER> prameters{};

		for (size_t i = 0; i < _desc.getDescriptorSize(); ++i) {
			auto& dParam = _desc.getDescriptor(i);

			D3D12_ROOT_PARAMETER param{};
			param.ParameterType = RootParameterTypeList.at(dParam.parameterType);
			param.ShaderVisibility = ShaderVisibilityList.at(dParam.shaderVisibility);
			param.Descriptor.RegisterSpace = dParam.registerSpace;
			param.Descriptor.ShaderRegister = dParam.shaderRegister;

			prameters.emplace_back(param);
		}

		for (size_t i = 0; i < _desc.getDescriptorTableSize(); ++i) {
			auto& dParam = _desc.getDescriptorTable(i);

			D3D12_DESCRIPTOR_RANGE ranges{};
			ranges.RangeType = DescriptorRangeList.at(dParam.desciropterRange);
			ranges.NumDescriptors = -1;
			ranges.BaseShaderRegister = dParam.shaderRegister;
			ranges.RegisterSpace = dParam.registerSpace;
			ranges.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

			D3D12_ROOT_PARAMETER param{};
			param.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			param.ShaderVisibility = ShaderVisibilityList.at(dParam.shaderVisibility);
			param.DescriptorTable.NumDescriptorRanges = dParam.numDescriptorRanges;
			param.DescriptorTable.pDescriptorRanges = &ranges;

			prameters.emplace_back(param);
		}

		//

		// Œã‚ÅÁ‚·
		D3D12_STATIC_SAMPLER_DESC staticSampler[1]{};
		staticSampler[0].Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
		staticSampler[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		staticSampler[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		staticSampler[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		staticSampler[0].MaxLOD = FLT_MAX;
		staticSampler[0].MinLOD = -FLT_MAX;
		staticSampler[0].MaxAnisotropy = 0;
		staticSampler[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		staticSampler[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

		D3D12_ROOT_SIGNATURE_DESC desc{};
		desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		desc.NumParameters = size;
		desc.pParameters = prameters.data();
		desc.NumStaticSamplers = 1;
		desc.pStaticSamplers = staticSampler;


		HRESULT hr{};

		D3DBlob signature{ nullptr }, error{ nullptr };
		hr = D3D12SerializeRootSignature(
			&desc,
			D3D_ROOT_SIGNATURE_VERSION_1,
			signature.GetAddressOf(),
			error.GetAddressOf()
		);

		if (FAILED(hr) || error) {
			return false;
		}

		hr = device->get()->CreateRootSignature(
			0,
			signature->GetBufferPointer(),
			signature->GetBufferSize(),
			IID_PPV_ARGS(rootSignature.GetAddressOf())
		);

		if (FAILED(hr)) {
			return false;
		}

		return true;
	}
	
}