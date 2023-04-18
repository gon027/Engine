#pragma once

#include <string>
#include <memory>
#include "Fwd.hpp"
#include "../../../engine/include/Core/ResourceOption.hpp"

namespace engine {

	namespace core {

		class IDevice {
		public:

			virtual ~IDevice() = default;

			virtual bool init(factory_ptr _factory) = 0;

			virtual std::wstring getAdapterName() const = 0;

			virtual resource_ptr createResource(
				const HeapType& _type, const ResourceDesc& _desc,
				enum ResouceStates _status, const ClearValue* _clearValue = nullptr
			) = 0;
		};

	}

	std::shared_ptr<core::IDevice> createDevice();

}