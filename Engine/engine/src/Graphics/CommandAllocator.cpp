#include "../../include/Graphics/CommandAllocator.hpp"
#include "../../include/EngineCore/EngineCore.hpp"
#include "../../include/Graphics/Device.hpp"

namespace engine {

	CommandAllocator::CommandAllocator()
		: commandAllocator(nullptr)
		, device(nullptr)
	{
	}

	CommandAllocator::~CommandAllocator()
	{
	}

	bool CommandAllocator::init()
	{
		{
			if (!device) device = EngineDevice()->get();
		}

		HRESULT hr = device->CreateCommandAllocator(
			D3D12_COMMAND_LIST_TYPE_DIRECT,
			IID_PPV_ARGS(commandAllocator.GetAddressOf())
		);

		if (FAILED(hr)) {
			return false;
		}

		return true;
	}

	void CommandAllocator::reset()
	{
		commandAllocator->Reset();
	}

}