#include "Adapter.hpp"

namespace engine {

    Adapter::Adapter()
        : adapters()
        , currentAdapterIndex(0)
    {
    }

    Adapter::~Adapter()
    {
        for (size_t i{ 0 }; i < adapters.size(); ++i) {
            if (adapters[i]) {
                adapters[i]->Release();
                adapters[i] = nullptr;
            }
        }
        adapters.clear();

        OutputDebugString("Dx12Adapter destructor called. \n");
    }

    bool Adapter::init(IDXGIFactory3* _factory)
    {
        IDXGIAdapter1* adapter{ nullptr };
        for (UINT index{ 0 }; _factory->EnumAdapters1(index, &adapter) != DXGI_ERROR_NOT_FOUND; ++index) {
            adapters.emplace_back(adapter);
        }

        std::string str{ "" };

        str = { "Adapter Count = " + std::to_string(adapters.size()) + "\n" };
        OutputDebugString(str.c_str());
        str = {"----- Adapter List ----------\n"};
        OutputDebugString(str.c_str());
        for (size_t i = 0; i < adapters.size(); ++i) {
            DXGI_ADAPTER_DESC1 desc;
            adapters[i]->GetDesc1(&desc);

            std::wstring s{ desc.Description };
            s += L'\n';
            OutputDebugStringW(s.c_str());

            adapterList.push_back(s);
        }
        str = { "-----------------------------\n" };
        OutputDebugString(str.c_str());

        if (adapter) {
            adapter->Release();
            adapter = nullptr;
        }

        return true;
    }

}