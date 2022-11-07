#pragma once

#include "../Library/Librarys.hpp"

#include "../include/IFactory.hpp"

namespace engine {

	class Dx12Factory : public core::IFactory {
	public:
		Dx12Factory();
		~Dx12Factory();

		bool init() override;

		inline IDXGIFactory3* get() const {
			return factory.Get();
		}

	private:
		DXGIFactory3 factory;
	};

}