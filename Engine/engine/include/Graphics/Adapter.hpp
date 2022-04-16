#pragma once

#include "../Library/Librarys.hpp"

namespace engine {

    class Adapter {
    public:
        Adapter();
        ~Adapter();

        bool init(IDXGIFactory3* _factory);

        inline IDXGIAdapter1* get(size_t _index) const {
            return adapters[_index];
        }

        inline IDXGIAdapter1* operator()(size_t _index) const {
            return adapters[_index];
        }

    private:
        std::vector<IDXGIAdapter1*> adapters;
    };

}