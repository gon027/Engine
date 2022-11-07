#pragma once

#include "../../lib/include/Fwd.hpp"
#include "ResourceOption.hpp"
#include "../../../engine/include/Type/Type.hpp"

namespace engine {

	enum ResourceType {
		Upload,
		// RenderTarget,
		DepthStencil,
		ShaderResource,
		UnorderedAccess
	};

	class Resource {
	public:
		virtual ~Resource() = default;

		virtual bool init(
			device_ptr _device, const HeapType& _type, const ResourceDesc& _desc,
			ResouceStates _status, const ClearValue* _clearValue = nullptr
		) = 0;

		virtual bool init(
			device_ptr _device, ResourceType _type, const ResourceDesc& _desc,
			ResouceStates _status, const ClearValue* _clearValue = nullptr
		) = 0;

		virtual bool writeToSubResource(
			const void* _data, u64 _width, u64 _height, u64 _rowPitch, u64 _slicePitch
		) = 0;

		virtual void* map() = 0;

		virtual void unMap() = 0;
	};

}