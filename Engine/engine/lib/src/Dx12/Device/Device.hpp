#pragma once

#include "../Library/Librarys.hpp"
#include "../include/Fwd.hpp"
#include "../include/IDevice.hpp"
#include "Adapter.hpp"

namespace engine {

	class Dx12Device : public core::IDevice {
	public:
		Dx12Device();
		~Dx12Device();

		bool init(factory_ptr _factory) override;

		resource_ptr createResource(
			const HeapType& _type, const ResourceDesc& _desc,
			ResouceStates _status, const ClearValue* _clearValue = nullptr
		) override;

		inline ID3D12Device* const get() const {
			return device.Get();
		}

		std::wstring getAdapterName() const override {
			return adapterName;
		}

	private:
		D3D12Device device;
		Adapter adapter;
		std::wstring adapterName;
	};

}