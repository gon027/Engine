#pragma once

#include <memory>

namespace engine {

	namespace core {

		class IFactory {
		public:
			virtual ~IFactory() = default;

			virtual bool init() = 0;
		};

	}

	std::shared_ptr<core::IFactory> createFactory();

}