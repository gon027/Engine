#include "Dx12Texture.hpp"
#include "../../../include/EngineCore/EngineCore.hpp"
#include "../Device/Device.hpp"

#include "../../../../include/Image/Image.hpp"

#include "../Lib/DirectXTex/DirectXTex.h"

#ifdef _DEBUG
#pragma comment(lib, "engine/Lib/src/Dx12/Lib/DirectXTex/x64/Debug/DirectXTex.lib")
#elif
#pragma comment(lib, "engine/Lib/Dx12/Lib/DirectXTex/x64/Release/DirectXTex.lib")
#endif

namespace engine {

	Dx12Texture::Dx12Texture()
		: width(0)
		, height(0)
		, resource(nullptr)
		, descriptorHeap()
	{
		

	}

	Dx12Texture::~Dx12Texture()
	{
	}

	bool Dx12Texture::load(device_ptr _device, const std::wstring& _path)
	{
		assert(_device != nullptr);
		auto* Dx12device = static_cast<Dx12Device*>(_device.get());

		DirectX::TexMetadata metaData{};
		DirectX::ScratchImage image{};
		{
			using namespace DirectX;

			HRESULT hr{};
			hr = LoadFromWICFile(
				_path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, &metaData, image
			);
			if (FAILED(hr)) {
				return false;
			}

			width = static_cast<unsigned int>(metaData.width);
			height = static_cast<unsigned int>(metaData.height);
		}

		{
			D3D12_RESOURCE_DESC desc{};
			desc.Dimension = static_cast<D3D12_RESOURCE_DIMENSION>(metaData.dimension);
			desc.Alignment = 0;
			desc.Width = width;
			desc.Height = (UINT)height;
			desc.DepthOrArraySize = (UINT16)metaData.depth;
			desc.MipLevels = (UINT16)metaData.mipLevels;
			desc.Format = metaData.format;
			desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
			desc.SampleDesc.Quality = 0;
			desc.SampleDesc.Count = 1;

			D3D12_HEAP_PROPERTIES prop{};
			prop.Type = D3D12_HEAP_TYPE_CUSTOM;
			prop.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
			prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
			prop.CreationNodeMask = 0;
			prop.VisibleNodeMask = 0;

			HRESULT hr = Dx12device->get()->CreateCommittedResource(
				&prop,
				D3D12_HEAP_FLAG_NONE,
				&desc,
				D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
				nullptr,
				IID_PPV_ARGS(resource.GetAddressOf())
			);
		}
		
		{
			u8* pDetaBegin{ nullptr };
			D3D12_BOX box{ 0, 0, 0, (UINT)metaData.width, (UINT)metaData.height, 1 };
			D3D12_RANGE range{ 0, 0 };

			HRESULT hr = resource->Map(0, &range, reinterpret_cast<void**>(pDetaBegin));
			if (FAILED(hr)) {
				return false;
			}

			hr = resource->WriteToSubresource(
				0,
				&box,
				image.GetImage(0, 0, 0)->pixels,
				static_cast<UINT>(image.GetImage(0, 0, 0)->rowPitch),
				static_cast<UINT>(image.GetImage(0, 0, 0)->slicePitch)
			);
			
			if (FAILED(hr)) {
				return false;
			}
			resource->Unmap(0, nullptr);
		}

		{
			if (!descriptorHeap.init(_device, 1, DescriptorType::CSV_SRV_UAV, DescriptorFlag::Visibe))
			{
				return false;
			}

			{
				D3D12_SHADER_RESOURCE_VIEW_DESC view{};
				view.Format = resource->GetDesc().Format;
				view.Texture2D.MipLevels = resource->GetDesc().MipLevels;
				view.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
				view.Texture2D.MostDetailedMip = 0;
				view.Texture2D.PlaneSlice = 0;
				view.Texture2D.ResourceMinLODClamp = 0.0f;
				view.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

				auto handle = descriptorHeap.getCpuHandle();
				Dx12device->get()->CreateShaderResourceView(resource.Get(), &view, handle);
			}
		}

		return true;
	}

	bool Dx12Texture::load(device_ptr _device, const Image& _image)
	{
		assert(_device != nullptr);
		auto* Dx12device = static_cast<Dx12Device*>(_device.get());

		width =  static_cast<unsigned int>(_image.getWidth());
		height = static_cast<unsigned int>(_image.getHeight());

		{
			D3D12_RESOURCE_DESC desc{};
			desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			desc.Alignment = 0;
			desc.Width = _image.getWidth();
			desc.Height = (UINT)_image.getHeight();
			desc.DepthOrArraySize = 1;
			desc.MipLevels = 1;
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
			desc.SampleDesc.Quality = 0;
			desc.SampleDesc.Count = 1;

			D3D12_HEAP_PROPERTIES prop{};
			prop.Type = D3D12_HEAP_TYPE_CUSTOM;
			prop.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
			prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
			prop.CreationNodeMask = 0;
			prop.VisibleNodeMask = 0;

			HRESULT hr = Dx12device->get()->CreateCommittedResource(
				&prop,
				D3D12_HEAP_FLAG_NONE,
				&desc,
				D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
				nullptr,
				IID_PPV_ARGS(resource.GetAddressOf())
			);
		}

		{
			u8* pDetaBegin{ nullptr };
			D3D12_BOX box{ 0, 0, 0, (UINT)_image.getWidth(), (UINT)_image.getHeight(), 1 };
			D3D12_RANGE range{ 0, 0 };

			HRESULT hr = resource->Map(0, &range, reinterpret_cast<void**>(pDetaBegin));
			if (FAILED(hr)) {
				return false;
			}

			hr = resource->WriteToSubresource(
				0,
				&box,
				_image.getData(),
				static_cast<UINT>(_image.getRowPitch()),
				static_cast<UINT>(_image.getSlicePitch())
			);

			if (FAILED(hr)) {
				return false;
			}
			resource->Unmap(0, nullptr);
		}

		if (!descriptorHeap.init(_device, 1, DescriptorType::CSV_SRV_UAV, DescriptorFlag::Visibe))
		{
			return false;
		}

		{
			D3D12_SHADER_RESOURCE_VIEW_DESC view{};
			view.Format = resource->GetDesc().Format;
			view.Texture2D.MipLevels = resource->GetDesc().MipLevels;
			view.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
			view.Texture2D.MostDetailedMip = 0;
			view.Texture2D.PlaneSlice = 0;
			view.Texture2D.ResourceMinLODClamp = 0.0f;
			view.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

			auto handle = descriptorHeap.getCpuHandle();
			Dx12device->get()->CreateShaderResourceView(resource.Get(), &view, handle);
		}

		return true;
	}

	unsigned int Dx12Texture::getWidth()
	{
		return width;
	}

	unsigned int Dx12Texture::getHeight()
	{
		return height;
	}

	ID3D12Resource* Dx12Texture::getResource() const
	{
		return resource.Get();
	}

	ID3D12DescriptorHeap* Dx12Texture::getHeap() const
	{
		return descriptorHeap.getDescriptorHeap();
	}

}