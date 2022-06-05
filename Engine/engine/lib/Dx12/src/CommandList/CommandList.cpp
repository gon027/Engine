#include <include/CommandList/CommandList.hpp>
#include <include/EngineCore/EngineCore.hpp>
#include <include/Device/Device.hpp>

namespace engine {

	CommandList::CommandList()
		: commandList(nullptr)
		, commandAllocator()
		, device(nullptr)
	{
	}

	CommandList::~CommandList()
	{
	}

	bool CommandList::init()
	{
		{
			if(!device) device = EngineDevice()->get();
		}

		if (!commandAllocator.init()) {
			return false;
		}

		HRESULT hr = device->CreateCommandList(
			0,
			D3D12_COMMAND_LIST_TYPE_DIRECT,
			commandAllocator.get(),
			nullptr,
			IID_PPV_ARGS(commandList.GetAddressOf())
		);

		if (FAILED(hr)) {
			return false;
		}

		close();

		return true;
	}

	void CommandList::reset()
	{
		commandAllocator.reset();

		commandList->Reset(commandAllocator.get(), nullptr);
	}

	void CommandList::close()
	{
		commandList->Close();
	}

}