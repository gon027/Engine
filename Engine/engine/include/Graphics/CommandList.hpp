#pragma once

#include "../Library/Librarys.hpp"
#include "CommandAllocator.hpp"

namespace engine {

	class CommandList {
	public:
		CommandList();
		~CommandList();
	
		bool init();

		void reset();

		void close();

		inline ID3D12GraphicsCommandList* const get() const {
			return commandList.Get();
		}

		inline ID3D12GraphicsCommandList* const operator->() const {
			return commandList.Get();
		}

	private:
		D3D12CommandList commandList;
		CommandAllocator commandAllocator;

	private:
		ID3D12Device* device;
	};

}