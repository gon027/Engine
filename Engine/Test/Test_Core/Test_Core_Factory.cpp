/*
#include "../../engine/include/EngineMain/EngineMain.hpp"

#include "../../engine/lib/include/IFactory.hpp"

#include "../../engine/lib/src/Dx12/Device/Factory.hpp"

#include <memory>

void gnMain() {
	using namespace engine;

	std::shared_ptr<core::IFactory> factory{ new Dx12Factory{} };
	if (!factory->init()) {
		OutputDebugString("Failed ...\n");
	}

	OutputDebugString("Dx12 Factory Successed!\n");
}
*/