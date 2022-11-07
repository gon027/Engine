#pragma once

#include "../Library/Librarys.hpp"

#include "../include/Fwd.hpp"
#include "../../../engine/include/Type/Type.hpp"
#include "../../../engine/include/Core/Resource.h"
#include "../../../engine/include/Core/ResourceOption.hpp"

namespace engine {

	class Dx12Resource : public Resource {
	public:
		Dx12Resource();
		~Dx12Resource();

		bool init(
			device_ptr _device, const HeapType& _type, const ResourceDesc& _desc,
			ResouceStates _status, const ClearValue* _clearValue = nullptr
		) override;

		bool init(
			device_ptr _device, ResourceType _type, const ResourceDesc& _desc,
			ResouceStates _status, const ClearValue* _clearValue = nullptr
		) override;

		bool writeToSubResource(
			const void* _data, u64 _width, u64 _height, u64 _rowPitch, u64 _slicePitch
		) override;

		void* map() override;

		void unMap() override;

		ID3D12Resource* get() {
			return resource.Get();
		}

	private:
		// u8* mapData; // u32*‚É•Ï‚¦‚é
		D3D12Resource resource;
		ResourceType resourceType;
	};

}