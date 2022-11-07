/*
#include "../../engine/include/EngineMain/EngineMain.hpp"

#include "../../engine/lib/include/EngineCore/EngineCore.hpp"
#include "../../engine/lib/include/IWindow.hpp"
#include "../../engine/lib/include/IDevice.hpp"
#include "../../engine/lib/include/IFactory.hpp"
#include "../../engine/lib/include/ICommandList.hpp"
#include "../../engine/lib/include/ICommandQueue.hpp"
#include "../../engine/lib/include/ISwapChain.hpp"

#include "../../engine/lib/src/Dx12/include/Buffer/Dx12Resource.hpp"

void gnMain() {
	using namespace engine;

	EngineCore::get()->init("windows", 640, 480);

	auto window = EngineWindow();
	auto device = EngineDevice();

	ResourceDesc desc{};
	desc.dimension = ResourceDimension::Buffer;
	desc.width = 255;
	desc.height = 1;
	desc.depthOrArraySize = 1;
	desc.mipLevels = 1;
	desc.format = TextureFormat::UNKNOWN;
	desc.layout = TextureLayout::RowMajor;
	desc.flags = ResourceFlags::None;

	resource_ptr resource = resource_ptr{ new Dx12Resource{} };
	if (resource->init(device, ResourceType::Upload, desc, ResouceStates::GenericRead)) {
		OutputDebugString("Yes\n");
	}
}
*/


/*
void gnMain() {
	using namespace engine;
	std::shared_ptr<Core::Resource> resource{ new Core::Dx12Resource{} };

	Core::HeapType type = Core::HeapType::Upload;
	Core::ResourceDesc desc{};
	Core::ResouceStates status{};
	bool is = resource->init(type, desc, status);

	if (is) {
		OutputDebugString("Yes\n");
	}
}
*/

/*
void gnMain() {
	using namespace engine;

	std::shared_ptr<core::IFactory> factory{ new Dx12Factory{} };
	if (factory->init()) {
		OutputDebugString("Factory Yes\n");
	}

	std::shared_ptr<core::IDevice> device{ new Dx12Device{} };
	if (device->init(factory.get())) {
		OutputDebugString("Device Yes\n");
	}

	core::HeapType type = core::HeapType::Upload;
	core::ResourceDesc desc{};
	desc.dimension = ResourceDimension::Buffer;
	desc.width = 255;
	desc.height = 1;
	desc.depthOrArraySize = 1;
	desc.mipLevels = 1;
	desc.format = TextureFormat::UNKNOWN;
	desc.layout = TextureLayout::RowMajor;
	desc.flags = ResourceFlags::None;

	core::ResouceStates status{};
	status = ResouceStates::GenericRead;

	auto resource = device->createResource(type, desc, status);
	if (resource.get()) {
		OutputDebugString("Resource Yes\n");
	}
	
}
*/