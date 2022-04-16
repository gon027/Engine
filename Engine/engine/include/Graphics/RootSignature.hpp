#pragma once

#include "../../include/Library/Librarys.hpp"

namespace engine {

	class RootSignature {
	public:
		static RootSignature create(const D3D12_ROOT_SIGNATURE_DESC& _desc);

	public:
		RootSignature();
		~RootSignature();

		bool init(const D3D12_ROOT_SIGNATURE_DESC& _desc);

		inline ID3D12RootSignature* const get() const {
			return rootSignature.Get();
		}

	private:
		D3D12RootSignature rootSignature;
	};

}