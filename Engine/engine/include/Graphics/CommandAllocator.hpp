#pragma once

#include "../Library/Librarys.hpp"

namespace engine {

	class CommandAllocator {
	public:
		CommandAllocator();
		~CommandAllocator();

		bool init();

		void reset();

		inline ID3D12CommandAllocator* const get() const {
			return commandAllocator.Get();
		}

		inline ID3D12CommandAllocator* const operator->() const {
			return commandAllocator.Get();
		}

	private:
		D3D12CommandAllocator commandAllocator;
		
	private:
		ID3D12Device* device;
	};

}