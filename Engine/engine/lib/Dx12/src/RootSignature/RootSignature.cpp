#include <include/RootSignature/RootSignature.hpp>
#include <include/EngineCore/EngineCore.hpp>
#include <include/Device/Device.hpp>

namespace engine {

	RootSignature RootSignature::create(const D3D12_ROOT_SIGNATURE_DESC& _desc)
	{
		RootSignature result{};
		result.init(_desc);

		return result;
	}

	RootSignature::RootSignature()
		: rootSignature(nullptr)
	{
	}

	RootSignature::~RootSignature()
	{
	}

	bool RootSignature::init(const D3D12_ROOT_SIGNATURE_DESC& _desc)
	{
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

		hr = EngineDevice()->get()->CreateRootSignature(
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