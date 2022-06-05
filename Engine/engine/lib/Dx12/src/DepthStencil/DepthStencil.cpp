#include <include/DepthStencil/DepthStencil.hpp>
#include <include/EngineCore/EngineCore.hpp>
#include <include/Device/Device.hpp>
#include <include/CommandList/CommandList.hpp>
#include "../../include/Window/Window.hpp"

namespace engine {

	DepthStencil::DepthStencil()
		: descriptorHeap(nullptr)
		, descriptorSize(0)
		, depthStencilResource(nullptr)
	{
	}

	DepthStencil::~DepthStencil()
	{
	}

	bool DepthStencil::init()
	{
		HRESULT hr{};

		{
			D3D12_DESCRIPTOR_HEAP_DESC desc{};
			desc.NumDescriptors = 1;
			desc.NodeMask = 0;
			desc.Type     = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
			desc.Flags    = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

			HRESULT hr = EngineDevice()->get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(descriptorHeap.GetAddressOf()));
			if (FAILED(hr)) {
				return false;
			}

			descriptorSize = EngineDevice()->get()->GetDescriptorHandleIncrementSize(desc.Type);
		}

		{
			D3D12_HEAP_PROPERTIES heap {
				D3D12_HEAP_TYPE_DEFAULT
			};

			CD3DX12_RESOURCE_DESC desc {
				D3D12_RESOURCE_DIMENSION_TEXTURE2D,
				0,
				static_cast<UINT64>(EngineWindow()->getWidth()),
				static_cast<UINT>(EngineWindow()->getHeight()),
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

			hr = EngineDevice()->get()->CreateCommittedResource(
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
			dsvDesc.Format        = DXGI_FORMAT_D32_FLOAT;
			dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
			dsvDesc.Flags         = D3D12_DSV_FLAG_NONE;
			dsvDesc.Texture2D.MipSlice = 0;

			auto handle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
			auto s = "Depth Stencil Handle = " + std::to_string(handle.ptr) + "\n";
			OutputDebugString(s.c_str());
			EngineDevice()->get()->CreateDepthStencilView(
				depthStencilResource.Get(),
				&dsvDesc,
				handle
			);
		}


		return true;
	}

	void DepthStencil::clearDepthStencil()
	{
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
	}
}