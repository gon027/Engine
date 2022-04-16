/*#include "../engine/include/Engine.hpp"
#include "../engine/include/Window/Window.hpp"
#include "../engine/include/Graphics/Adapter.hpp"
#include "../engine/include/Library/Librarys.hpp"
#include "../engine/include/Graphics/Factory.hpp"
#include "../engine/include/Graphics/Adapter.hpp"
#include "../engine/include/Graphics/Device.hpp"
#include "../engine/include/Graphics/CommandList.hpp"
#include "../engine/include/Graphics/CommandQueue.hpp"
#include "../engine/include/Graphics/RenderTarget.hpp"
#include "../engine/include/Graphics/RenderingPipeline2D.hpp"
#include "../engine/include/EngineCore/EngineCore.hpp"

void gnMain() {
	using namespace engine;

	App::init("aaa", 640, 480);

	auto a = EngineDevice()->get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	std::string s{ std::to_string(a) + "\n"};
	OutputDebugString(s.c_str());

	{
		D3D12_DESCRIPTOR_HEAP_DESC desc{};
		desc.NumDescriptors = 1;
		desc.NodeMask = 0;
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

		D3D12DescriptorHeap desctiptor{nullptr};
		HRESULT hr = EngineDevice()->get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(descriptor.GetAddressOf()));
		if (FAILED(hr)) {
			return;
		}

		auto ds = EngineDevice()->get()->GetDescriptorHandleIncrementSize(desc.Type);
	}

	while (App::update()) {
		App::begin();

		App::end();
	}
}
*/