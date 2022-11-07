#include "DepthStencil.hpp"
#include "../../Windows/Window.hpp"
#include "../Device/Device.hpp"
#include "../CommandList/Dx12CommandList.hpp"

namespace engine {

	Dx12DepthStencil::Dx12DepthStencil()
		: descriptorHeap(nullptr)
		, descriptorSize(0)
		, depthStencilResource(nullptr)
	{
	}

	Dx12DepthStencil::~Dx12DepthStencil()
	{
		OutputDebugString("Dx12DepthStencil destructor called. \n");
	}

	bool Dx12DepthStencil::init(window_ptr _window, device_ptr _device)
	{
		assert(_window != nullptr);
		assert(_device != nullptr);

		auto* device = static_cast<Dx12Device*>(_device.get());

		HRESULT hr{};

		{
			D3D12_DESCRIPTOR_HEAP_DESC desc{};
			desc.NumDescriptors = 1;
			desc.NodeMask = 0;
			desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
			desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

			hr = device->get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(descriptorHeap.GetAddressOf()));
			if (FAILED(hr)) {
				return false;
			}

			descriptorSize = device->get()->GetDescriptorHandleIncrementSize(desc.Type);
		}

		{
			D3D12_HEAP_PROPERTIES heap{
				D3D12_HEAP_TYPE_DEFAULT
			};

			CD3DX12_RESOURCE_DESC desc{
				D3D12_RESOURCE_DIMENSION_TEXTURE2D,
				0,
				640, //static_cast<UINT64>(_window.get()->getWidth()),
				480, //static_cast<UINT>(_window.get()->getHeight()),
				1,
				0,
				DXGI_FORMAT_D32_FLOAT,
				1,
				0,
				D3D12_TEXTURE_LAYOUT_UNKNOWN,
				D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
			};

			D3D12_CLEAR_VALUE value{};
			value.Format = DXGI_FORMAT_D32_FLOAT;
			value.DepthStencil.Depth = 1.0f;
			value.DepthStencil.Stencil = 0;

			hr = device->get()->CreateCommittedResource(
				&heap,
				D3D12_HEAP_FLAG_NONE,
				&desc,
				D3D12_RESOURCE_STATE_DEPTH_WRITE,
				&value,
				IID_PPV_ARGS(depthStencilResource.GetAddressOf())
			);

			if (FAILED(hr)) {
				return false;
			}

			// 深度ステンシルビューの設定
			D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
			dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
			dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
			dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
			dsvDesc.Texture2D.MipSlice = 0;

			auto handle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
			device->get()->CreateDepthStencilView(
				depthStencilResource.Get(),
				&dsvDesc,
				handle
			);
		}

		return true;
	}

	void Dx12DepthStencil::clearDepthStencil()
	{
		/*
		// 深度ステンシルビューをクリア
		EngineCommand()->get()->ClearDepthStencilView(
			descriptorHeap->GetCPUDescriptorHandleForHeapStart(),
			D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
			1.0f,
			0,
			0,
			nullptr
		);

		EngineCommand()->get()->OMSetStencilRef(0);
		*/
	}

	std::shared_ptr<core::DepthStencil> createDepthStencil() {
		return std::shared_ptr<Dx12DepthStencil> {
			new Dx12DepthStencil{}
		};
	}
}