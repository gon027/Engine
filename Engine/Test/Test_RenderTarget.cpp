// #include "EngineMain/EngineMain.hpp"
// #include "../engine/include/Window/Window.hpp"
// #include "../engine/include/EngineCore/EngineCore.hpp"
// #include "../engine/include/Graphics/Factory.hpp"
// #include "../engine/include/Graphics/Device.hpp"
// #include "../engine/include/Graphics/CommandList.hpp"
// 
// #include "../engine/include/Graphics/RenderTarget.hpp"
// #include "../engine/include/Graphics/DepthStencil.hpp"

/*
void gnMain() {
	using namespace engine;

	try {
		Engine()->init();
	}
	catch (const std::exception&) {
		return;
	}

	RenderTarget renderTarget{};
	if (!renderTarget.init()) {
		OutputDebugString("NO\n");
		return;
	}

	// DepthStencil depth{};
	// if (!depth.init()) {
	// 	return;
	// }

	while (EngineWindow()->update()) {
		Engine()->begin();


		renderTarget.setRenderTargetView(D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

		renderTarget.clearScreen();
		renderTarget.setRenderTargets();
		//depth.clear();

		renderTarget.setRenderTargetView(D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);


		EngineCommand()->close();
		EngineCommand()->execute();
		renderTarget.present();
		EngineCommand()->wait();
		renderTarget.swapCurrentBackBufferIndex();

		Sleep(1);
	}

}
*/