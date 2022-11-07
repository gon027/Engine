/*
#include "../../engine/include/EngineMain/EngineMain.hpp"

#include "../../engine/lib/include/IDevice.hpp"
#include "../../engine/lib/include/IFactory.hpp"
#include "../../engine/lib/include/ICommandList.hpp"

#include "../../engine/lib/src/Dx12/Device/Factory.hpp"
#include "../../engine/lib/src/Dx12/Device/Device.hpp"
#include "../../engine/lib/src/Dx12/CommandList/Dx12CommandList.hpp"

void gnMain() {
	using namespace engine;

	std::shared_ptr<core::IFactory> factory{ new Dx12Factory{} };
	if (!factory->init()) {
		OutputDebugString("Dx12 Factory Failed ... \n");
	}
	OutputDebugString("Dx12 Factory Successed! \n");

	std::shared_ptr<core::IDevice> device{ new Dx12Device{} };
	if (!device->init(factory)) {
		OutputDebugString("Dx12 Device Failed ... \n");
	}
	OutputDebugString("Dx12 Device Successed! \n");

	std::shared_ptr<core::ICommandList> commandList{ new Dx12CommandList{} };
	if (!commandList->init(device)) {
		OutputDebugString("Dx12 CommandList Failed ... \n");
	}
	OutputDebugString("Dx12 CommandList Successed! \n");
}
*/