#pragma once

#include "../Library/Librarys.hpp"

namespace engine {

    class Adapter {
    public:
        Adapter();
        ~Adapter();

        bool init(IDXGIFactory3* _factory);

        inline IDXGIAdapter1* get(size_t _index) {
            currentAdapterIndex = _index;
            return adapters[_index];
        }

        inline IDXGIAdapter1* operator[](size_t _index) {
            currentAdapterIndex = _index;
            return adapters[_index];
        }

        inline std::wstring getAdapterName() {
            return adapterList[currentAdapterIndex];
        }

    private:
        std::vector<IDXGIAdapter1*> adapters;
        std::vector<std::wstring> adapterList;
        size_t currentAdapterIndex;
    };

}