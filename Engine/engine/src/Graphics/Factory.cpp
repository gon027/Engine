#include "../../include/Graphics/Factory.hpp"

namespace engine {

	namespace {

		UINT getDebugFlag() {
			UINT debugFlag{ 0 };

		#if _DEBUG
			Microsoft::WRL::ComPtr<ID3D12Debug> debug{ nullptr };
			Microsoft::WRL::ComPtr<ID3D12Debug1> debug1{ nullptr };
			D3D12GetDebugInterface(IID_PPV_ARGS(debug.GetAddressOf()));

			if (debug) {
				debug->EnableDebugLayer();
			}

			debug->QueryInterface(IID_PPV_ARGS(debug1.GetAddressOf()));
			debug1->SetEnableGPUBasedValidation(true);

			debugFlag |= DXGI_CREATE_FACTORY_DEBUG;
		#endif

			return debugFlag;
		}

	}

	Factory::Factory()
		: factory(nullptr)
	{
	}

	Factory::~Factory()
	{
		factory.Reset();
	}

	bool Factory::init()
	{
		HRESULT hr = CreateDXGIFactory2(getDebugFlag(), IID_PPV_ARGS(factory.ReleaseAndGetAddressOf()));
		if (FAILED(hr)) {
			return false;
		}

		return true;
	}
}