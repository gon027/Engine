#pragma once

#include <include/Library/Librarys.hpp>

namespace engine {

	class Device {
	public:
		Device();
		~Device();

		bool init(IDXGIFactory3* _factory);

		inline ID3D12Device* const get() const {
			return device.Get();
		}

	private:
		D3D12Device device;
	};

}