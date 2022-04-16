#pragma once

#include "../Library/Librarys.hpp"

namespace engine {

	class Factory {
	public:
		Factory();
		~Factory();

		bool init();

		inline IDXGIFactory3* get() const {
			return factory.Get();
		}

		inline IDXGIFactory3* operator->() const {
			return factory.Get();
		}

		inline IDXGIFactory3* operator()() const {
			return factory.Get();
		}

	private:
		DXGIFactory3 factory;
	};

}