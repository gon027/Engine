#include "Factory.hpp"

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

	Dx12Factory::Dx12Factory()
		: factory(nullptr)
	{
	}

	Dx12Factory::~Dx12Factory()
	{
		factory.Reset();
		OutputDebugString("Dx12Factory destructor called. \n");
	}

	bool Dx12Factory::init()
	{
		HRESULT hr = CreateDXGIFactory2(getDebugFlag(), IID_PPV_ARGS(factory.ReleaseAndGetAddressOf()));
		if (FAILED(hr)) {
			return false;
		}

		return true;
	}

	std::shared_ptr<core::IFactory> createFactory() {
		return std::shared_ptr<Dx12Factory> {
			new Dx12Factory{}
		};
	}
}